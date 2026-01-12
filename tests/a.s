.globl _main
_main:
    stp x29, x30, [sp, #-16]!
    mov x29, sp
    sub sp, sp, #48
    movz w10, #4
    str w10, [x29, #-16]
    movz w10, #3
    str w10, [x29, #-20]
    movz w10, #0
    str w10, [x29, #-24]
    movz w10, #1
    str w10, [x29, #-28]
continue_Labeltmp.4:
    ldr w10, [x29, #-24]
    ldr w11, [x29, #-20]
    cmp w10, w11
    movz w10, #0
    str w10, [x29, #-32]
    cset w10, lt
    str w10, [x29, #-32]
    ldr w11, [x29, #-32]
    movz w10, #0
    cmp w10, w11
    b.eq break_Labeltmp.4
    ldr w10, [x29, #-28]
    str w10, [x29, #-36]
    ldr w11, [x29, #-36]
    ldr w10, [x29, #-16]
    mul w11, w11, w10
    str w11, [x29, #-36]
    ldr w10, [x29, #-36]
    str w10, [x29, #-28]
    ldr w10, [x29, #-24]
    str w10, [x29, #-40]
    ldr w11, [x29, #-40]
    movz w10, #1
    add w11, w11, w10
    str w11, [x29, #-40]
    ldr w10, [x29, #-40]
    str w10, [x29, #-24]
    b continue_Labeltmp.4
break_Labeltmp.4:
    ldr w0, [x29, #-28]
    b __func_exit
    movz w0, #0
    b __func_exit
__func_exit:
    add sp, sp, #48
    ldp x29, x30, [sp], #16
    ret
