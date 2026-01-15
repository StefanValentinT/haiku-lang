/* Make sure we recognize that EAX is live at exit.
 * Don't inspect assembly; just validate the program's behavior.
 * Note: only works as intended once we've implemented register coalescing.
 *
 * This test program is generated from templates/chapter_20_templates/reg_live_at_exit.c.jinja
 * */


int glob = 10;
int glob2 = 0;





int target(void) {
    int x = glob + 1;  
    glob2 = x + glob;
    return x;
}

int main(void) {
    int retval = target();
    check_one_int(retval, 11);
    check_one_int(glob2, 21);
    return 0;
}