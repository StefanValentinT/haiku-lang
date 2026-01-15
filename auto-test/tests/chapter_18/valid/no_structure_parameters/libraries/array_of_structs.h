/* Test that we can pass a pointer to an array of structures as a parameter */

struct inner {
    long l;
    char arr[2];
};  

struct outer {
    char a;          
    struct inner b;  

};  

int validate_struct_array(struct outer *struct_array);