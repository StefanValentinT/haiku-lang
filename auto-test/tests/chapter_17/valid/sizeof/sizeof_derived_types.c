/* Make sure we accurately calculate the size of derived (pointer and array)
 * types */

void *malloc(unsigned long size);

int main(void) {
    
    
    if (sizeof(int[2]) != 8) {
        return 1;
    }

    
    
    if (sizeof(char[3][6][17][9]) != 2754) {
        return 2;
    }

    
    
    
    
    if (sizeof(int[4294967297L][100000000]) != 1717986918800000000l) {
        return 3;
    }

    
    
    if (sizeof(int *) != 8) {
        return 4;
    }

    if (sizeof(int(*)[2][4][6]) !=
        8) {  
        return 5;
    }

    if (sizeof(char *) != 8) {
        return 6;
    }

    
    
    
    
    if (sizeof(double(*([3][4]))[2]) != 96) {
        return 7;
    }

    return 0;
}