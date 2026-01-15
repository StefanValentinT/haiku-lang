/* Test passing union types along w/ other arguments according to ABI */


int main(void) {
    
    union two_doubles two_xmm = { {-10.0, -11.0} }; 
    union one_int one_gp = { 13.0 }; 
    struct has_union one_gp_struct = { -24, {0} };
    one_gp_struct.u.i = 123456789;

    if (!pass_unions_and_structs(1, 2, one_gp_struct, 4.0, two_xmm, one_gp, 100, 120, 130)) {
        return 1;
    }

    
    if (!pass_gp_union_in_memory(two_xmm, one_gp_struct, -1, -2, -3, -4, -5, -6, one_gp)) {
        return 2;
    }

    
    union two_doubles two_xmm_2 = { {33e4, 55e6 } };

    if (!pass_xmm_union_in_memory(1.0, 2.0, two_xmm, two_xmm, 3.0, 4.0, two_xmm_2)) {
        return 3;
    }

    
    
    union char_arr two_gp = { "+_)(*&^%$#" };
    if (!pass_borderline_union(1, 2, 3, 4, 5, two_gp)) {
        return 4;
    }

    

    
    
    two_xmm_2.arr[0] = two_xmm_2.arr[0] * 2;
    two_xmm_2.arr[1] = two_xmm_2.arr[1] * 2;
    if (!pass_borderline_xmm_union(two_xmm, 9.0, 8.0, 7.0, 6.0, 5.0, two_xmm_2)) {
        return 5;
    }

    
    
    union gp_and_xmm mixed_regs = { {0, 150.5} };
    if (!pass_mixed_reg_in_memory(101.2, 102.3, 103.4, 104.5, 75, 76, 77, 78, 79, 80, mixed_regs)) {
        return 6;
    }

    
    union uneven uneven = { "boop" };
    if (!pass_uneven_union_in_memory(1100, 2200, 3300, 4400, 5500, mixed_regs, one_gp, uneven)) {
        return 7;
    }

    
    
    union lotsa_doubles mem = { {66., 77., 88.} };
    if (!pass_in_mem_first(mem, mixed_regs, two_gp, one_gp_struct)) {
        return 8;
    }

    return 0;
}