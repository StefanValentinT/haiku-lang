/* Test for void expressions in for loop header */

int putchar(int c);  

int letter;
void initialize_letter(void) {
    letter = 'Z';
}

void decrement_letter(void) {
    letter = letter - 1;
}

int main(void) {
    
    for (initialize_letter(); letter >= 'A';
         letter = letter - 1) {
        putchar(letter);
    }

    
    for (letter = 'A'; letter <= 90; (void)(letter = letter + 1)) {
        putchar(letter);
    }

    
    for (initialize_letter(); letter >= 65; decrement_letter()) {
        putchar(letter);
    }
    return 0;
}