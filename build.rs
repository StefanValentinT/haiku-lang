use time::OffsetDateTime;

fn main() {
    println!("cargo:rerun-if-changed=build.rs");

    let now = OffsetDateTime::now_utc();

    let dev_build = format!(
        "DevBuild {:02}:{:02} {}.{}.{}",
        now.hour() as u32,
        now.minute() as u32,
        now.day() as u32,
        now.month() as u32,
        now.year()
    );

    println!("cargo:rustc-env=DEV_BUILD={}", dev_build);
}
