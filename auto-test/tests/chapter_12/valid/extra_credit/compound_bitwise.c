int main(void) {

    unsigned long ul = 18446460386757245432ul; 
    ul &= -1000; 
    if (ul != 18446460386757244952ul /* 0xfffe_fdfc_fbfa_f818 */) {
        return 1; 
    }

    ul |= 4294967040u; 

    if (ul != 18446460386824683288ul /* 0xfffe_fdfc_ffff_ff18 */) {
        return 2; 
    }

    
    
    
    int i = 123456;
    unsigned int ui = 4042322160u; 
    long l = -252645136; 
    
    
    
    
    if (ui ^= l) {
        return 3; 
    }

    
    if (ui) {
        return 4; 
    }
    
    if (i != 123456) {
        return 5;
    }
    if (l != -252645136) {
        return 6;
    }

    return 0; 
}