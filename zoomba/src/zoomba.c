#include <stdio.h>
#include <stdlib.h>


int main() {
    int dimension;
    dimension = scanf("%d\n" ,&dimension); //Η διάσταση του δωματίου
    int zoombaX, zoombaY;
    zoombaX = scanf("%d", &zoombaX); //Η αρχική θέση της zoomba
    zoombaY = scanf("%d", &zoombaY);
    int targetX, targetY;
    targetX = scanf("%d", &targetX); //Το σημείο που θα φτάσει η zoomba.
    targetY = scanf("%d", &targetY);

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