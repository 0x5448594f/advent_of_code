#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int char_is_vowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int contain_couple_char(char str[3]) {
    char UNWANTED_COUPLE_CHAR[4][3] = { "ab", "cd", "pq", "xy" };
    int len = sizeof(UNWANTED_COUPLE_CHAR) / sizeof(char[2]);

    for ( int i = 0; i < len; i++) {
        if ( strcmp(str, UNWANTED_COUPLE_CHAR[i]) == 0 ) {
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
        int len = sizeof(buffer) / sizeof(char);

        int vowel_count = 0;
        int has_vowels = 0;
        int has_doubles = 0;
        int contains_unwanted_pair = 0;

        if ( char_is_vowel(buffer[len-2]) ) { vowel_count++; }

        for ( size_t i = 0; i+1 < strlen(buffer); i++) {
            char couple[3];
            couple[0] = buffer[i];
            couple[1] = buffer[i+1];

            if ( contains_unwanted_pair == 0 ) {
                contains_unwanted_pair = contain_couple_char(couple);
            }

            if ( char_is_vowel(couple[0]) ) {
                vowel_count++;

                if ( vowel_count >= 3 ) { has_vowels = 1; }
            }

            if ( couple[0] == couple[1] && has_doubles != 1 ) { has_doubles = 1; }
        }

        if ( has_vowels && !contains_unwanted_pair && has_doubles ) { valid_strings++; }
    }

    printf("There is %d valid strings.\n", valid_strings);

    return 0;
}
