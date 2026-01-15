/* Test that copying an aggregate value with Copy, Load, Store,
 * CopyFromOffset or CopyToOffset doesn't clobber the stack.
 * To do this, we store some bytes on the stack, copy the struct,
 * then validate those bytes haven't changed. This test assumes structures
 * are allocated on the stack in the same order they're declared/initialized,
 * so we know which objects are right next to the one we copy to. If this assumption
 * doesn't hold, clobbers may overwrite stack padding instead of data that we
 * validate, and go undetected).
 */

void exit(int status);

struct chars {
    char char_array[3];
};

static struct chars y = {{0, 1, 2}};
static struct chars *ptr;  




void validate_array(char *char_array, int start, int code) {

    for (int i = 0; i < 3; i = i + 1) {
        if (char_array[i] != start + i) {
            exit(code);
        }
    }
    return;
}






void increment_y(void) {
    y.char_array[0] = y.char_array[0] + 3;
    y.char_array[1] = y.char_array[1] + 3;
    y.char_array[2] = y.char_array[2] + 3;
}


int test_copy(void) {
    
    struct chars a = {"abc"};
    struct chars b = {"xyz"};
    struct chars c = {"def"};
    
    b = y;
    
    validate_array(a.char_array, 'a', 1);
    validate_array(b.char_array, 0, 2);
    validate_array(c.char_array, 'd', 3);
    return 0;
}











static struct chars to_validate;
void validate_static(int start, int code) {
    validate_array(to_validate.char_array, start, code);
}

int test_load(void) {
    static struct chars b; 
    
    struct chars a = {"ghi"};
    
    b = *ptr; 
    
    to_validate = a;
    validate_static('g', 4);
    to_validate = b;
    validate_static(3, 5);
    return 0;
}


int test_store(void) {
    
    struct chars struct_array[3] = {{"jkl"}, {"xyz"}, {"mno"}};
    struct chars *ptr = &struct_array[1];

    
    *ptr = y;

    
    validate_array(struct_array[0].char_array, 'j', 6);
    validate_array(struct_array[1].char_array, 6, 7);
    validate_array(struct_array[2].char_array, 'm', 8);
    return 0;
}


struct chars_container {
    char c;
    struct chars chars;
    char arr[3];
};









int test_copy_from_offset(void) {
    
    struct chars a = {"pqr"};

    static struct chars b = {"xyz"};
    static struct chars_container container = {100, {{9, 10, 11}}, "123"};

    
    b = container.chars;

    
    to_validate = a;
    validate_static('p', 9);
    to_validate = b;
    validate_static(9, 10);
    return 0;
}


int test_copy_to_offset(void) {

    struct chars_container container = {
        'x', {{0, 0, 0}}, "stu"
    };

    
    container.chars = y;

    
    if (container.c != 'x') {
        exit(11);
    }

    validate_array(container.chars.char_array, 12, 12);

    validate_array(container.arr, 's', 13);

    return 0;
}

int main(void) {
    ptr = &y;
    test_copy();
    increment_y();
    test_load();
    increment_y();
    test_store();
    increment_y();
    test_copy_from_offset();
    increment_y();
    test_copy_to_offset();
    return 0;
}