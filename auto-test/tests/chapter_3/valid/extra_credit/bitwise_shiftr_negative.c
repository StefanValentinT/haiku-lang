/* Make sure we use arithmetic rather than logical right shift.
 * NOTE: right bitshift of negative value is implementation-defined;
 * we follow GCC and use sign extension
 * (see https:
 * */
int main(void) {
    return -5 >> 30;
}