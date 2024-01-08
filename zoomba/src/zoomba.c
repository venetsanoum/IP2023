#include <stdio.h>
#include <stdlib.h>


int main() {
     int dimension;
    if (scanf("%d", &dimension) != 1) {
        fprintf(stderr, "Error reading dimension\n");
        return 1;
    }

    int zoombaX, zoombaY, targetX, targetY;
    if (scanf("%d %d %d %d", &zoombaX, &zoombaY, &targetX, &targetY) != 4) {
        fprintf(stderr, "Error reading positions\n");
        return 1;
    }
    
    int **room;
    room = malloc(dimension * sizeof(int*));
    if(!room) {
        fprintf(stderr, "Failed to allocate memory\n");
        return 1;
    }

    for (int i = 0; i < dimension; i++) {
        room[i] = malloc(dimension * sizeof(int));
        if(!room[i]) {
            fprintf(stderr, "Failed to allocate memory\n");
            free(room);
        }
    }





    
    for (int i = 0; i < dimension; i++) {
        free(room[i]);
    }
    free(room);

    return 0;
}