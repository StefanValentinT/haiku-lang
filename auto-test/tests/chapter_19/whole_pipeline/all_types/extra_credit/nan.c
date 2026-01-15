



int target(void) {
    double nan = 0.0 / 0.0;
    if (nan < 0.0 || nan == 0.0 || nan > 0.0 || nan <= 0.0 || nan >= 0.0)
        return 1;

    if (1 > nan || 1 == nan || 1 > nan || 1 <= nan || 1 >= nan)
        return 2;

    if (nan == nan)
        return 3;

    if (!(nan != nan)) { 
        return 4;
    }

    
    
    nan = nan * 4;
    if (nan == nan) {
        return 5;
    }

    nan = 22e2 / nan;
    if (nan == nan) {
        return 6;
    }

    if (-nan == -nan) {
        return 7;
    }

    if (!nan) { 
        return 8;
    }

    return 0; 
}

int main(void) {
    return target();
}