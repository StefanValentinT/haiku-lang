use assert_cmd::cargo;
use std::fs;
use std::path::{Path, PathBuf};
use tabled::{Table, Tabled};

const FILE_COL_WIDTH: usize = 25;
const TYPE_COL_WIDTH: usize = 10;
const EXPECTED_COL_WIDTH: usize = 20;
const ACTUAL_COL_WIDTH: usize = 60;
const PASSED_COL_WIDTH: usize = 6;

struct CompilerResult {
    stdout: String,
    stderr: String,
    success: bool,
    exit_code: Option<i32>,
    signal: Option<i32>,
}

enum TestKind {
    Expect {
        expect_out: Option<String>,
        expect_ret: Option<String>,
    },
    Fail,
    Skip,
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

fn extract_tag(contents: &str, tag: &str) -> Option<String> {
    let start = format!("<{}>", tag);
    let end = format!("</{}>", tag);
    contents.find(&start).map(|s| {
        let s = s + start.len();
        contents[s..contents.find(&end).unwrap()].trim().to_string()
    })
}

fn classify_test(contents: &str) -> TestKind {
    if contents.contains("<fail>") {
        TestKind::Fail
    } else {
        let expect_out = extract_tag(contents, "expect_out");
        let expect_ret = extract_tag(contents, "expect_ret");

        if expect_out.is_some() || expect_ret.is_some() {
            TestKind::Expect {
                expect_out,
                expect_ret,
            }
        } else {
            TestKind::Skip
        }
    }
}

fn run_compiler(path: &Path) -> CompilerResult {
    let mut cmd = cargo::cargo_bin_cmd!("compiler");
    let output = cmd.arg(path).output().expect("Failed to run compiler");

    #[cfg(unix)]
    use std::os::unix::process::ExitStatusExt;

    CompilerResult {
        stdout: String::from_utf8_lossy(&output.stdout).replace("\r\n", "\n"),
        stderr: String::from_utf8_lossy(&output.stderr).to_string(),
        success: output.status.success(),
        exit_code: output.status.code(),
        signal: cfg!(unix).then(|| output.status.signal()).flatten(),
    }
}

fn pad_truncate(s: &str, len: usize) -> String {
    let mut res: String = s.chars().take(len).collect();
    while res.chars().count() < len {
        res.push(' ');
    }
    res
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
                fs::remove_dir_all(&path).ok();
            } else {
                remove_build_folders(&path);
            }
        }
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
        let result = run_compiler(&path);

        let (ty, expected, actual, passed) = match &test_kind {
            TestKind::Fail => {
                let actual = if let Some(sig) = result.signal {
                    format!("signal {}", sig)
                } else if let Some(code) = result.exit_code {
                    format!("exit {}", code)
                } else {
                    "<no result>".to_string()
                };

                (
                    "Fail".to_string(),
                    "failure".to_string(),
                    actual.clone(),
                    !result.success,
                )
            }

            TestKind::Expect {
                expect_out,
                expect_ret,
            } => {
                let mut ok = true;
                let mut exp = String::new();
                let mut act = String::new();

                if let Some(out) = expect_out {
                    exp.push_str(&format!("out: {}", out));
                    act.push_str(&format!("out: {}", result.stdout.trim_end()));
                    ok &= result.stdout.trim_end() == out;
                }

                if let Some(ret) = expect_ret {
                    let code = result
                        .exit_code
                        .map(|c| c.to_string())
                        .unwrap_or("<signal>".into());
                    if !exp.is_empty() {
                        exp.push_str(", ");
                        act.push_str(", ");
                    }
                    exp.push_str(&format!("ret: {}", ret));
                    act.push_str(&format!("ret: {}", code));
                    ok &= code == *ret;
                }

                (
                    "Expect".to_string(),
                    exp,
                    act,
                    ok && result.stderr.is_empty(),
                )
            }

            TestKind::Skip => ("Skip".to_string(), "".to_string(), "".to_string(), true),
        };

        rows.push(TestRow {
            file: pad_truncate(&path.file_name().unwrap().to_string_lossy(), FILE_COL_WIDTH),
            ty: pad_truncate(&ty, TYPE_COL_WIDTH),
            expected: pad_truncate(&expected, EXPECTED_COL_WIDTH),
            actual: pad_truncate(&actual, ACTUAL_COL_WIDTH),
            passed: pad_truncate(if passed { "✅" } else { "❌" }, PASSED_COL_WIDTH),
        });

        if !passed && !matches!(test_kind, TestKind::Skip) {
            eprintln!("==== Test failed: {} ====", path.display());
            eprintln!("stdout:\n{}", result.stdout);
            eprintln!("stderr:\n{}", result.stderr);
            panic!("Test failed");
        }
    }

    println!("\n{}", Table::new(rows));
    remove_build_folders(test_dir);
}
