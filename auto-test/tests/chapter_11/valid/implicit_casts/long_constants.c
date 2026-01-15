int main(void) {

    /* A constant with an l suffix always has long type */

    
    if (2147483647l + 2147483647l < 0l) {
        return 1;
    }
    /* if a constant is too large to store as an int,
     * it's automatically converted to a long, even if it
     * doesn't have an 'l' suffix
     * if we parsed 19327352832 as an int, it would be negative
     */
    if (19327352832 < 100l) { 
        return 2;
    }
    return 0;
}