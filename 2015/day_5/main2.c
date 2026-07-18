#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int has_double_in_word(char str[3], char* word, size_t current_index, size_t len) {
    for ( size_t i = current_index+2; i+1 < len; i++) {
        char couple[3];
        couple[0] = word[i];
        couple[1] = word[i+1];

        if ( strcmp(str, couple ) == 0) {
           return 1; 
        }
    }

    return 0;
}

int main() {
    int valid_strings = 0;

    char buffer[100];
    FILE* file = fopen("data", "r");

    if ( file == NULL ) {
        printf("Error: Impossible to read the file.");
        return 1;
    }


    while (fgets(buffer, sizeof(buffer), file)) {
        size_t len = strlen(buffer);

        int has_double = 0;
        int valid_repeat = 0;

        for ( size_t i = 0; i+1 < len; i++) {
            char couple[3];
            couple[0] = buffer[i];
            couple[1] = buffer[i+1];

            if ( buffer[i+2] && couple[0] != couple[1] && couple[0] == buffer[i+2] ) {
                valid_repeat = 1;
            }

            if ( has_double == 0 ) {
                has_double = has_double_in_word(couple, buffer, i, len);
            }
        }

        if ( has_double && valid_repeat ) { valid_strings++; }

    }

    printf("There is %d valid strings.", valid_strings);
    return 0;
}
