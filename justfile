default:
    cargo fmt
    cargo build
    cd ./auto-test && python3.10 test_compiler ../target/debug/compiler --chapter 9 --stage tacky


run filename *args:
    cargo fmt
    cargo run -- {{filename}} {{args}}