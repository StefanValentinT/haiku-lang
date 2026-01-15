/* Test constant folding of JumpIfZero and JumpIfNotZero instructions
 * resulting from && and || operations, with operand types other than int.
 * Identical to chapter_19/constant_folding/int_only/fold_conditional_jump.c
 * but with non-int operands
 * */




int target_jz_to_jmp(void) {
    return 0l && 0; 
}




int target_remove_jz(void) {
    return 1u && 1.; 
}





int target_jnz_to_jmp(void) {
    return 3.5 || 99ul; 
}





int target_remove_jnz(void) {
    return 0ul || 1; 
}

int main(void) {
    if (target_jz_to_jmp() != 0) {
        return 1;
    }
    if (target_remove_jz() != 1) {
        return 2;
    }
    if (target_jnz_to_jmp() != 1) {
        return 3;
    }
    if (target_remove_jnz() != 1) {
        return 4;
    }
    return 0; 
}