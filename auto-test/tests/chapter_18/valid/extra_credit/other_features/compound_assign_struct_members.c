
struct inner {
    double a;
    char b;
    int *ptr;
};

struct outer {
    unsigned long l;
    struct inner *in_ptr;
    struct inner in_array[4];
    int bar;
};

int main(void) {
    int i = -1;
    int i2 = -2;
    struct inner si = {150., -12, &i};
    struct outer o = {
                      18446744073709551615UL,
                      
                      &si,
                      
                      {si, {-20e20, 120, 0}, {0, 0, 0}, {1, 1, &i2}},
                      
                      2000};

    
    si.a += 10;  
    if (si.a != 160) {
        return 1;  
    }

    
    
    o.in_array[0].b -= 460;  
    if (o.in_array[0].b != 40) {
        return 2;  
    }

    
    o.in_array[1].a *= -4;  
    if (o.in_array[1].a != 80e20) {
        return 4;  
    }

    
    o.in_ptr->a /= 5;  
    
    if (si.a != 32) {
        return 5;  
    }

    
    (&o)->l %= o.bar;  
    if (o.l != 1615) {
        return 6;  
    }

    
    o.in_ptr = o.in_array;
    if ((o.in_ptr += 3)->a != 1) {
        return 7;  
    }
    if (*o.in_ptr->ptr != -2) {
        return 8;  
    }

    
    o.in_ptr -= 1u;
    if (o.in_ptr->a || o.in_ptr->b || o.in_ptr->ptr) {
        return 9;  
    }

    
    if (si.a != 32 || si.b != -12 || si.ptr != &i) {
        return 10;  
    }

    if (o.l != 1615) {
        return 11;  
    }

    if (o.in_ptr != &o.in_array[2]) {
        return 12;  
    }

    if (o.in_array[0].a != 150. || o.in_array[0].b != 40 ||
        o.in_array[0].ptr != &i) {
        return 13;  
    }

    if (o.in_array[1].a != 80e20 || o.in_array[1].b != 120 ||
        o.in_array[1].ptr) {
        return 14;  
    }

    if (o.in_array[2].a || o.in_array[2].b || o.in_array[2].ptr) {
        return 15;  
    }

    if (o.in_array[3].a != 1 || o.in_array[3].b != 1 ||
        o.in_array[3].ptr != &i2) {
        return 16;  
    }

    if (o.bar != 2000) {
        return 17;
    }

    return 0;
}