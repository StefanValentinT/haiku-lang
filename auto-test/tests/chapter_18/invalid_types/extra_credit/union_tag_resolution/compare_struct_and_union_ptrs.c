/* If 'struct tag' shadows 'union tag' or vice versa, these two types are
 * distinct so pointers to them cannot be compared
 */

int main(void) {
    struct tag;
    struct tag *struct_ptr = 0;
    {
        union tag;
        union tag *union_ptr = 0;
        
        return (struct_ptr == union_ptr);
    }
}