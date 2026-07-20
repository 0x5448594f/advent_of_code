#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const size_t WIDTH = 1000;
const size_t HEIGHT = 1000;

typedef struct {
    size_t x;
    size_t y;
} pos;

// -1 = error
//  0 = turn off
//  1 = turn on
//  2 = toggle
int determine_action(char* token) {
    if ( strcmp(token, "toggle") == 0 ) {
        return 2;
    } else if ( strcmp(token, "turn" ) == 0 ) {
        token = strtok(NULL, " ");

        if ( strcmp(token, "on") == 0 ) {
            return 1;
        } else if ( strcmp(token, "off") == 0 ) {
            return 0;
        }     
    }

    printf("ERROR: Invalid token\n");
    return -1;
}

pos determine_position(char* token) {
    char* saveptr;
    char* first_int = strtok_r(token, ",", &saveptr);
    int x = atoi(first_int);
    char* second_int = strtok_r(NULL, " ", &saveptr);
    int y = atoi(second_int);

    pos new_pos = { x, y };

    return new_pos;
}

int main() {
    int* arr = calloc(WIDTH * HEIGHT, sizeof(int));

    char buffer[100];
    FILE* file = fopen("data", "r");

    if ( file == NULL ) {
        printf("Error: Impossible to read the file.");
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), file)) { 
        char* token = strtok(buffer, " ");

        int action = determine_action(token);

        token = strtok(NULL, " "); // Get position

        pos pos_1 = determine_position(token);
        token = strtok(NULL, " "); // skip "through"
        token = strtok(NULL, " "); // Get position
        pos pos_2 = determine_position(token);

        for ( size_t y = pos_1.y; y <= pos_2.y; y++ ) {
            for ( size_t x = pos_1.x; x <= pos_2.x; x++ ) {
                int real_pos = x + y*WIDTH;

                // Response level 1 :
                // if ( action == 0 ) {
                //     arr[real_pos] = 0;
                // } else if ( action == 1 ) {
                //     arr[real_pos] += 1;
                // } else if ( action == 2 ) {
                //     arr[real_pos] = !arr[real_pos];
                // }

                if ( action == 0 && arr[real_pos] > 0 ) {
                    arr[real_pos] -= 1;
                } else if ( action == 1 ) {
                    arr[real_pos] += 1;
                } else if ( action == 2 ) {
                    arr[real_pos] += 2;
                }
            }
        }

    }

    // Response level 1:
    // int lights_lit = 0;
    // for ( size_t i = 0; i < WIDTH * HEIGHT; i++ ) {
    //     if ( arr[i] == 1 ) {
    //         lights_lit++;
    //     }
    //
    // }
    //printf("%d lights lit.", lights_lit);

    // Response level 2:
    int total_brightness = 0;
    for ( size_t i = 0; i < WIDTH * HEIGHT; i++ ) {
        if ( arr[i] > 0 ) {
            total_brightness += arr[i];
        }
    }
    printf("Total brightness = %d.", total_brightness);

    return 0;
}
