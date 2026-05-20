#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare (const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}

void get_dimentions(int* arr, char* str) {
    char* token = strtok(str, "x");
    arr[0] = strtol(token, NULL, 10);

    for ( int n = 1; n < 3; n++ ) {
        token = strtok(NULL, "x");

        if ( token == NULL ) {
            break;
        }

        arr[n] = strtol(token, NULL, 10);
    }
}

int calcule_require_wrapping_paper(int* faces) {
    qsort(faces, 3, sizeof(int), compare);
    int min = faces[0];

    return 2*faces[0] + 2*faces[1] + 2*faces[2] + min;
}

int calcule_require_ribbon(int* dimentions) {
    int sort_dim[3] = { dimentions[0], dimentions[1], dimentions[2] };
    qsort (sort_dim, 3, sizeof(int), compare);

    return ( sort_dim[0]*2 + sort_dim[1]*2 ) + ( dimentions[0] * dimentions[1] * dimentions[2] );
}


int main(void) {
    FILE* file = fopen("data", "r");

    if ( file == NULL ) {
        printf("Error: Impossible to read the file.");
        return 1;
    }

    char buffer[100];
    int total_wp = 0;
    int total_ribbon = 0;
    int dimentions[3];
    int faces[3];

    while (fgets(buffer, sizeof(buffer), file)) {
        get_dimentions(dimentions, buffer);
        faces[0] = dimentions[0] * dimentions[1];
        faces[1] = dimentions[1] * dimentions[2];
        faces[2] = dimentions[2] * dimentions[0];

        total_wp += calcule_require_wrapping_paper(faces);
        total_ribbon += calcule_require_ribbon(dimentions);
    }

    printf("Part I: %d\n", total_wp);
    printf("Part II: %d\n", total_ribbon);

    return 0;
}
