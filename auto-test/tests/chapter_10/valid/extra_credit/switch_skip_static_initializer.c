int a = 3;
int main(void) {
    switch (a) {
        case 1:;
            /* Since x is static, it's initialized at program startup,
             * so its value will be 10 even though we jump over this declaration
             */
            static int x = 10;
            
            
            x = 0;
        case 3:
            return x; 
    }
    return 0; 
}