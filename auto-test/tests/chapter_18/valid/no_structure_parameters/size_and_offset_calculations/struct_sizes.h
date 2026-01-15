

struct eight_bytes {
    int i;   
    char c;  
             
};

struct two_bytes {
    char arr[2];  
                  
};

struct three_bytes {
    char arr[3];  
                  
};

struct sixteen_bytes {
    struct eight_bytes eight;  
    struct two_bytes two;      
    struct three_bytes three;  
    
    
};

struct seven_bytes {
    struct two_bytes two;      
    struct three_bytes three;  
    struct two_bytes two2;     
};                             

struct twentyfour_bytes {
    struct seven_bytes seven;  
    
    struct sixteen_bytes sixteen;  
};

struct twenty_bytes {
    struct sixteen_bytes sixteen;  
    struct two_bytes two;          
    
};  

struct wonky {
    char arr[19];
};  

struct internal_padding {
    char c;
    
    double d;
};  

struct contains_struct_array {
    char c;  
    
    struct eight_bytes struct_array[3];  
};                                       
