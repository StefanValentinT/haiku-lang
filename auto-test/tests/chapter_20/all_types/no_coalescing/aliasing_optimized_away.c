
/* Make sure we store a variable in a register if it's aliased in the
 * original program, but the aliasing gets optimized away.
 */


int target(int arg) {
    int *optimized_away = &arg; 
    return arg + 10;
}
