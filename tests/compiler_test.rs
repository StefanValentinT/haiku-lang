use assert_cmd::Command;
use std::fs;
use std::path::PathBuf;

#[test]
fn hk_golden_tests() {
    let test_dir = PathBuf::from("tests");

    for entry in fs::read_dir(&test_dir).expect("Failed to read test directory") {
        let entry = entry.expect("Failed to read entry");
        let path = entry.path();
        if path.extension().and_then(|s| s.to_str()) != Some("hk") {
            continue;
        }

        println!("Testing {}", path.display());

        let contents = fs::read_to_string(&path)
            .unwrap_or_else(|_| panic!("Failed to read {}", path.display()));
        let expected_output = extract_expected_output(&contents)
            .unwrap_or_else(|| panic!("No expected output in {}", path.display()));

        let mut cmd = Command::cargo_bin("compiler").expect("Binary not found");
        let output = cmd.arg(&path).output().expect("Failed to run compiler");

        assert!(
            output.status.success(),
            "Compiler failed on {}: {}",
            path.display(),
            String::from_utf8_lossy(&output.stderr)
        );

        let stdout = String::from_utf8_lossy(&output.stdout);

        // Compare stdout to expected
        assert_eq!(
            stdout.trim(),
            expected_output.trim(),
            "Test failed for {}",
            path.display()
        );
    }
}

fn extract_expected_output(contents: &str) -> Option<String> {
    let start_tag = "$EXPECTED_OUTPUT_START$";
    let end_tag = "$EXPECTED_OUTPUT_END$";

    let start = contents.find(start_tag)? + start_tag.len();
    let end = contents.find(end_tag)?;

    Some(contents[start..end].trim().to_string())
}
