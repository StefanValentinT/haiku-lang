/* Modify a parameter of structure type
 * */

int main(void) {
    struct inner s_inner = {2.0, 3};
    if (!modify_simple_struct(s_inner)) {
        return 1;
    }
    
    if (s_inner.d != 2.0 || s_inner.i != 3) {
        return 2;
    }

    
    struct outer s_o = {{4.0, 5}, &s_inner, 1000l};
    if (!modify_nested_struct(s_o)) {
        return 3;
    }
    
    
    if (s_o.s.d != 4.0 || s_o.s.i != 5 || s_o.l != 1000l) {
        return 4;
    }

    if (s_o.ptr != &s_inner) {
        return 5;
    }

    
    if (s_o.ptr->d != 10.0 || s_o.ptr->i != 11) {
        return 6;
    }

    return 0;  
}