#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    Position pos;
    int value;
} House;

void print_houses(House* houses, int house_count) {
    for ( int i = 0; i < house_count; i++ ) {
        House house = houses[i];

        printf("House %d: value: %d \n", i, house.value);
    }
}

int find_house_index(House* arr, int size_arr, Position pos) {
    int house_index = -1; // -1 = not found

    for ( int i = 0; i < size_arr; i++ ) {
        if ( arr[i].pos.y == pos.y && arr[i].pos.x == pos.x ) {
            house_index = i;
            break;
        }
    }

    return house_index;
}

House* add_house(House* houses, int house_count, Position pos) {
    House new_house = {
        pos: { pos.x, pos.y },
        value: 1
    };

    House* temp_houses = (House*)malloc( house_count * sizeof(House));
    
    if ( house_count > 1 ) {
        memcpy(temp_houses, houses, (house_count - 1) * sizeof(House));
    }

    temp_houses[house_count-1] = new_house;

    free(houses);

    return temp_houses;
}

int main() {
    char buffer[100];
    FILE* file = fopen("data", "r");

    if ( file == NULL ) {
        printf("Error: Impossible to read the file.");
        return 1;
    }

    Position santa_position = { x: 0, y: 0 };
    Position robot_santa_position = { x: 0, y: 0 };

    House base_house  = {
        pos: { santa_position.x, santa_position.y },
        value: 1
    };
    int house_count = 1;
    House* houses = (House*)malloc( house_count * sizeof(House));
    houses[0] = base_house;
    bool toggle = false;

    while (fgets(buffer, sizeof(buffer), file)) {
        for ( int i = 0; i < strlen(buffer); i++ ) {
            char character = buffer[i];

            switch ( character ) {
                case '^':
                    if ( toggle ) {
                        robot_santa_position.y--;
                    } else {
                        santa_position.y--;
                    }

                    break;

                case '>':
                    if ( toggle ) {
                        robot_santa_position.x++;
                    } else {
                        santa_position.x++;
                    }

                    break;

                case '<':
                    if ( toggle ) {
                        robot_santa_position.x--;
                    } else {
                        santa_position.x--;
                    }

                    break;

                case 'v':
                    if ( toggle ) {
                        robot_santa_position.y++;
                    } else {
                        santa_position.y++;
                    }

                    break;

                default:
                    break;
            }


            if ( toggle ) {
                int house_find = find_house_index(houses, house_count, robot_santa_position);

                if ( house_find == -1 ) {
                    house_count++;
                    houses = add_house(houses, house_count, robot_santa_position);
                } else {
                    houses[house_find].value++;
                }

                toggle = false;
            } else {
                int house_find = find_house_index(houses, house_count, santa_position);

                if ( house_find == -1 ) {
                    house_count++;
                    houses = add_house(houses, house_count, santa_position);
                } else {
                    houses[house_find].value++;
                }

                toggle = true;
            }
        }
    }

    printf("%d\n", house_count);

    return 0;
}
