

unsigned unsigned_arr[4] = {4294967295U, 4294967294U, 4294967293U, 4294967292U};

int idx = 2;
long long_idx = 1;

int main(void) {
    long_idx = -long_idx; 
    
    unsigned_arr[1] += 2;  
    if (unsigned_arr[1]) {
        return 1;  
    }
    unsigned_arr[idx] -= 10.0;
    if (unsigned_arr[idx] != 4294967283U) {
        return 2;  
    }

    unsigned *unsigned_ptr = unsigned_arr + 4;  
    unsigned_ptr[long_idx] /= 10;  
    if (unsigned_arr[3] != 429496729U) {
        return 3;  
    }

    
    unsigned_ptr[long_idx *= 2] *= unsigned_arr[0];
    if (unsigned_arr[2] != 13) {
        return 4;  
    }

    
    if ((unsigned_arr[idx + long_idx] %= 10) != 5) {
        return 5;  
    }

    
    
    if (unsigned_arr[0] != 5u) {
        return 6;  
    }

    if (unsigned_arr[1]) {  
        return 7;           
    }

    if (unsigned_arr[2] != 13) {
        return 8;  
    }

    if (unsigned_arr[3] != 429496729U) {
        return 9;  
    }

    return 0;
}