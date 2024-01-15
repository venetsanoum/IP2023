#include <stdio.h>
#include <stdlib.h>
//Συνάρτηση που βρίσκει τη βέλτιστη διαδρομή από ένα σημείο σε ένα άλλο.
void findPath(int **grid, int startX, int startY, int targetX, int targetY, int n){

}

int main() {
     int dimension;
    if (scanf("%d", &dimension) != 1) { //Διάσταση του δωματίου.
        fprintf(stderr, "Error reading dimension\n");
        return 1;
    }

    int zoombaX, zoombaY, targetX, targetY; //Σημείο εκκίνησης και σημείο προορισμού
    if (scanf("%d %d %d %d", &zoombaX, &zoombaY, &targetX, &targetY) != 4) {
        fprintf(stderr, "Error reading positions\n");
        return 1;
    }

    int **room; //Δυναμική δέσμευση μνήμης για το κωδικοποιημένο δωμάτιο
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
        for (int j = 0; j < dimension; j++) {
            char cell;
            if (scanf(" %c", &cell) != 1 || (cell != '0' && cell != '1')) { //Δέχεται έναν έναν χαρακτήρα και ελέγχει ότι είναι 0 ή 1.
                fprintf(stderr, "Invalid input for room layout\n");
                
                for (int k = 0; k <= i; k++) {
                    free(room[k]);
                }
                free(room);
                return 1;
            }
            room[i][j] = cell - '0'; // Μετατροπή χαρακτήρα σε ακέραιο
        }
    }

    findPath(room, zoombaX, zoombaY, targetX, targetY, dimension);//Κλήση συνάρτησης για την εύρεση της βέλτιστης διαδρομής 

    for (int i = 0; i < dimension; i++) {//Αποδέσμευση του πίνακα για το δωμάτιο.
        free(room[i]);
    }
    free(room);

    return 0;
}