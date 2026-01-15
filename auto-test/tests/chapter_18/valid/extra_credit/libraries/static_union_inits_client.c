




union simple s = {217};



union has_union h = {{77}};




struct has_union_array my_struct = {
    {{{'a'}}, {{'b'}}, {{'c'}}}, '#', {'!'}
};




union has_union all_zeros;



union with_padding padded_union_array[3] = {
    {"first string"}, {"string #2"}, {
        "string #3"
    }
};

int main(void) {
    if (!validate_simple()) {
        return 1;
    }

    if (!validate_has_union()){
        return 2;
    }

    if (!validate_has_union_array()) {
        return 3;
    }

    if (!validate_uninitialized()) {
        return 4;
    }

    if (!validate_padded_union_array()) {
        return 5;
    }

    return 0;
}