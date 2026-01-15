
int main(void) {
    int arr[4] = {-1, -2, -3, -4};
    int *ptr = arr;
    int idx = 2;

    
    
    if ((ptr++[idx++] *= 3) != -9) {
        return 1; 
    }
    if (*ptr != -2) {
        return 2; 
    }
    if (idx != 3) {
        return 3; 
    }
    idx--;
    
    if ((--ptr)[3] += 4) {
        return 4; 
    }

    
    if (arr[0] != -1 || arr[1] != -2 || arr[2] != -9 || arr[3] != 0) {
        return 5; 
    }
    return 0; 
}