install:
    cargo fmt
    cargo build
    cargo install --path . --force

run filename *args:
    haiku {{filename}} {{args}}

test:
    cargo fmt
    cargo test -- --nocapture
