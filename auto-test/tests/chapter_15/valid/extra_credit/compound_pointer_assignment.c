

int i = 4;

int int_array(void) {
    int arr[6] = {1, 2, 3, 4, 5, 6};
    int *ptr = arr;

    
    if (*(ptr += 5) != 6) {
        return 1; 
    }
    if (ptr[0] != 6) {
         return 2; 
    }

    if (ptr != arr + 5) {
        return 3;
    }

    
    if (*(ptr -=3) != 3) {
        return 4; 
    }
    if (ptr[0] != 3) {
        return 5;
    }
    if (ptr != arr + 2) {
        return 6;
    }

    
    if ((ptr += i - 1) != arr + 5) {
        return 7;
    }

    if (*ptr != 6) {
        return 8;
    }

    
    
    if ((ptr -= (4294967295U + i)) != arr + 2) {
        return 9;
    }

    if (*ptr != 3) {
        return 10;
    }

    long l = 9223372036854775807l;
    if ((ptr += l - 9223372036854775806l) != arr + 3) {
        return 11;
    }

    if (*ptr != 4) {
        return 12;
    }

    return 0; 
}

int double_array(void) {
    
    static double arr[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    double *ptr = arr;

    
    if (*(ptr += 5) != 6) {
        return 1; 
    }
    if (ptr[0] != 6) {
         return 2; 
    }

    if (ptr != arr + 5) {
        return 3;
    }

    
    if (*(ptr -=3) != 3) {
        return 4; 
    }
    if (ptr[0] != 3) {
        return 5;
    }
    if (ptr != arr + 2) {
        return 6;
    }

    
    if ((ptr += i - 1) != arr + 5) {
        return 7;
    }

    if (*ptr != 6) {
        return 8;
    }

    
    
    if ((ptr -= (4294967295U + i)) != arr + 2) {
        return 9;
    }

    if (*ptr != 3) {
        return 10;
    }

    long l = 9223372036854775807l;
    if ((ptr += l - 9223372036854775806l) != arr + 3) {
        return 11;
    }

    if (*ptr != 4) {
        return 12;
    }

    return 0;
}

int main(void) {
    int result;

    if ((result = int_array())) {
        return result; 
    }
    if ((result = double_array())) {
        return result + 12; 
    }
    return 0; 
}