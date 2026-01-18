use assert_cmd::cargo;
use std::fs;
use std::path::{Path, PathBuf};
use tabled::{Table, Tabled};

// Constants for column widths
const FILE_COL_WIDTH: usize = 20;
const TYPE_COL_WIDTH: usize = 5;
const EXPECTED_COL_WIDTH: usize = 20;
const ACTUAL_COL_WIDTH: usize = 60;
const PASSED_COL_WIDTH: usize = 5;

fn find_hk_files(dir: &Path) -> Vec<PathBuf> {
    let mut files = Vec::new();
    for entry in fs::read_dir(dir).expect("Failed to read test directory") {
        let entry = entry.expect("Failed to read entry");
        let path = entry.path();
        if path.is_dir() {
            files.extend(find_hk_files(&path));
        } else if path.extension().and_then(|s| s.to_str()) == Some("hk") {
            files.push(path);
        }
    }
    files
}

fn extract_panic_message(stderr: &str) -> String {
    stderr
        .find("panicked at")
        .and_then(|start_idx| {
            let mut lines = &mut stderr[start_idx..].lines();
            lines.next()?;
            lines.next().map(|s| s.trim().to_string())
        })
        .unwrap_or_else(|| "<no panic>".to_string())
}

fn extract_expected_output(contents: &str) -> Option<String> {
    let start_tag = "<expect>";
    let end_tag = "</expect>";
    contents.find(start_tag).map(|start| {
        let start = start + start_tag.len();
        contents[start..contents.find(end_tag).unwrap()]
            .trim()
            .to_string()
    })
}

fn classify_test(contents: &str) -> TestKind {
    if contents.contains("<fail>") {
        TestKind::Fail
    } else if let Some(expect) = extract_expected_output(contents) {
        TestKind::Expect(expect)
    } else {
        TestKind::Skip
    }
}

enum TestKind {
    Expect(String),
    Fail,
    Skip,
}

fn remove_build_folders(dir: &Path) {
    if !dir.is_dir() {
        return;
    }
    for entry in fs::read_dir(dir).expect("Failed to read directory") {
        let entry = entry.expect("Failed to read entry");
        let path = entry.path();
        if path.is_dir() {
            if path.file_name().unwrap() == "build" {
                fs::remove_dir_all(&path).unwrap_or_else(|_| {
                    panic!("Failed to remove build directory: {}", path.display())
                });
            } else {
                remove_build_folders(&path);
            }
        }
    }
}

#[derive(Tabled)]
struct TestRow {
    file: String,
    #[tabled(rename = "Type")]
    ty: String,
    expected: String,
    actual: String,
    passed: String,
}

fn pad_truncate(s: &str, len: usize) -> String {
    let mut res: String = s.chars().take(len).collect();
    while res.chars().count() < len {
        res.push(' ');
    }
    res
}

struct CompilerResult {
    stdout: String,
    stderr: String,
    success: bool,
}

fn run_compiler(path: &Path) -> CompilerResult {
    let mut cmd = cargo::cargo_bin_cmd!("compiler");
    let output = cmd.arg(path).output().expect("Failed to run compiler");

    let stdout = String::from_utf8_lossy(&output.stdout).trim().to_string();
    let stderr = String::from_utf8_lossy(&output.stderr).trim().to_string();

    CompilerResult {
        stdout,
        stderr,
        success: output.status.success(),
    }
}

#[test]
fn compiler_tests() {
    let test_dir = Path::new("tests");
    let files = find_hk_files(test_dir);
    let mut rows = Vec::new();

    for path in files {
        let contents = fs::read_to_string(&path)
            .unwrap_or_else(|_| panic!("Failed to read {}", path.display()));

        let test_kind = classify_test(&contents);

        let (ty_str, expected_str, actual_output, passed) = match &test_kind {
            TestKind::Fail => {
                let result = run_compiler(&path);
                let actual = if result.stderr.is_empty() {
                    pad_truncate("<no error message>", ACTUAL_COL_WIDTH)
                } else {
                    pad_truncate(&extract_panic_message(&result.stderr), ACTUAL_COL_WIDTH)
                };
                let expected = pad_truncate("Failure", EXPECTED_COL_WIDTH);
                let pass = !result.success && !result.stderr.is_empty() && result.stdout.is_empty();
                (pad_truncate("Err", TYPE_COL_WIDTH), expected, actual, pass)
            }

            TestKind::Expect(expected) => {
                let result = run_compiler(&path);
                let actual = pad_truncate(&result.stdout, ACTUAL_COL_WIDTH);
                let expected_padded = pad_truncate(expected, EXPECTED_COL_WIDTH);
                let pass = result.success && result.stderr.is_empty() && result.stdout == *expected;
                (
                    pad_truncate("Some", TYPE_COL_WIDTH),
                    expected_padded,
                    actual,
                    pass,
                )
            }

            TestKind::Skip => {
                let empty = pad_truncate("", ACTUAL_COL_WIDTH);
                (
                    pad_truncate("", TYPE_COL_WIDTH),
                    pad_truncate("", EXPECTED_COL_WIDTH),
                    empty.clone(),
                    true,
                )
            }
        };

        let passed_col = match &test_kind {
            TestKind::Skip => pad_truncate("Skip", PASSED_COL_WIDTH),
            TestKind::Fail | TestKind::Expect(_) => {
                pad_truncate(if passed { "✅" } else { "❌" }, PASSED_COL_WIDTH)
            }
        };

        rows.push(TestRow {
            file: pad_truncate(&path.file_name().unwrap().to_string_lossy(), FILE_COL_WIDTH),
            ty: ty_str,
            expected: expected_str,
            actual: actual_output,
            passed: passed_col,
        });

        if !passed && !matches!(test_kind, TestKind::Skip) {
            panic!("Test failed: {}", path.display());
        }
    }

    println!("\n{}", Table::new(rows));

    remove_build_folders(test_dir);
}
