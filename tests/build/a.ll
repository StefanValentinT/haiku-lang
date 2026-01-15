define i32 @fib(i32 %arg_tmp.0) {
entry:
  %tmp.8 = alloca i32
  %tmp.2 = alloca i32
  %tmp.9 = alloca i32
  %tmp.7 = alloca i32
  %tmp.5 = alloca i32
  %tmp.6 = alloca i32
  %tmp.0 = alloca i32
  store i32 %arg_tmp.0, i32* %tmp.0
  %r0 = load i32, i32* %tmp.0
  %r2 = icmp slt i32 %r0, 2
  %r1 = zext i1 %r2 to i32
  store i32 %r1, i32* %tmp.2
  %r3 = load i32, i32* %tmp.2
  %r4 = icmp eq i32 %r3, 0
  br i1 %r4, label %if_else4, label %cont4
cont4:
  %r5 = load i32, i32* %tmp.0
  ret i32 %r5
  br label %if_end3
if_else4:
  %r6 = load i32, i32* %tmp.0
  %r7 = sub i32 %r6, 1
  store i32 %r7, i32* %tmp.5
  %r8 = load i32, i32* %tmp.5
  %r9 = call i32 @fib(i32 %r8)
  store i32 %r9, i32* %tmp.6
  %r10 = load i32, i32* %tmp.0
  %r11 = sub i32 %r10, 2
  store i32 %r11, i32* %tmp.7
  %r12 = load i32, i32* %tmp.7
  %r13 = call i32 @fib(i32 %r12)
  store i32 %r13, i32* %tmp.8
  %r14 = load i32, i32* %tmp.6
  %r15 = load i32, i32* %tmp.8
  %r16 = add i32 %r14, %r15
  store i32 %r16, i32* %tmp.9
  %r17 = load i32, i32* %tmp.9
  ret i32 %r17
if_end3:
  ret i32 0
}

define i32 @main() {
entry:
  %tmp.1 = alloca i32
  %tmp.10 = alloca i32
  %r0 = call i32 @fib(i32 10)
  store i32 %r0, i32* %tmp.10
  %r1 = load i32, i32* %tmp.10
  store i32 %r1, i32* %tmp.1
  %r2 = load i32, i32* %tmp.1
  ret i32 %r2
  ret i32 0
}

