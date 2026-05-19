#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char buffer[100];

    FILE* file;
    file = fopen("data", "r");

    if ( file == NULL ) {
        printf("ERROR: Not able to open your file.");
        return 1;
    }

    int floor = 0;
    int index = 0;
    bool part_2_trigger = false;

    while(fgets(buffer, sizeof(buffer), file)) {
        for ( int n = 0; buffer[n] != 0; n++ ) {
            if ( floor == -1 && !part_2_trigger ) {
                printf("Part II: %d -> %d\n", index, floor);
                part_2_trigger = true;
            }

            char character = buffer[n];

            if ( character == '(' ) {
                floor++;
            } else if ( character == ')' ) {
                floor--;
            }

            index++;
        }
    }

    fclose(file);
    printf("Part I: %d\n", floor);
    return 0;
}
