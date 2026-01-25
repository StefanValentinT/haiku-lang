pub fn preprocess(input: &str) -> String {
    let mut output = String::new();
    let chars: Vec<char> = input.chars().collect();
    let mut i = 0;
    let mut block_depth = 0;

    while i < chars.len() {
        if block_depth == 0 && chars[i] == '#' && i + 1 < chars.len() && chars[i + 1] == '[' {
            block_depth = 1;
            i += 2;
            continue;
        }

        if block_depth > 0 && chars[i] == '#' && i + 1 < chars.len() && chars[i + 1] == '[' {
            block_depth += 1;
            i += 2;
            continue;
        }

        if block_depth > 0 && chars[i] == ']' && i + 1 < chars.len() && chars[i + 1] == '#' {
            block_depth -= 1;
            i += 2;
            continue;
        }

        if block_depth == 0 && chars[i] == '#' {
            while i < chars.len() && chars[i] != '\n' {
                i += 1;
            }
            if i < chars.len() {
                output.push('\n');
                i += 1;
            }
            continue;
        }

        if block_depth == 0 {
            output.push(chars[i]);
        }

        i += 1;
    }

    output
}
