/* Test that we don't read past the bounds of a structure when passing it as a
 * parameter: pass a structure parameter that ends at the end
 * of a page, where the next page isn't mapped. If we read past the end of the
 * structure we'll trigger a memory access violation and crash the program.
 * */


struct nine_bytes {
    char arr[11];
};



extern struct nine_bytes on_page_boundary;

int f(struct nine_bytes in_reg, int a, int b, int c, int d, int e,
      struct nine_bytes on_stack) {
    
    for (int i = 0; i < 9; i = i + 1) {
        char in_reg_c = in_reg.arr[i];
        char on_stack_c = on_stack.arr[i];
        if (i == 2) {
            
            if (in_reg_c != 4 || on_stack_c != 4) {
                return 1;
            }
        } else if (i == 3) {
            
            if (in_reg_c != 5 || on_stack_c != 5) {
                return 2;
            }
        } else if (i == 8) {
            
            if (in_reg_c != 6 || on_stack_c != 6) {
                return 3;
            }
        } else {
            
            if (in_reg_c || on_stack_c) {
                return 4;
            }
        }
    }

    
    if (a != 101 || b != 102 || c != 103 || d != 104 || e != 105) {
        return 5;
    }

    return 0;  
}

int main(void) {
    on_page_boundary.arr[2] = 4;
    on_page_boundary.arr[3] = 5;
    on_page_boundary.arr[8] = 6;
    
    return f(on_page_boundary, 101, 102, 103, 104, 105,
             on_page_boundary);  
}