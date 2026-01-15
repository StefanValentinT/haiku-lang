int main(void) {
    unsigned int ui = 10u;

    switch(ui) {
        case 4294967295u: 
            return 0;
        case 1099511627775l: 
            return 1;
        default: return 2;
    }
}