/* Load instruction generates all aliased variables */
long *pass_and_return(long *ptr) {
    return ptr;
}

int main(void) {
    long l;
    long *ptr = &l;
    long *other_ptr = pass_and_return(ptr);  
    l = 10;  
             
    return *other_ptr;  
}