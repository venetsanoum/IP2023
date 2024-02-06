#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node { //Αυτοαναφορική δομή Node
    int row, col; //Συντεταγμένες του κόμβου στο δωμάτιο
    int f, g, h; //Τιμές των συναρτήσεων κόστους που θα δημιουργηθούν
    struct Node* parent; //Δείκτης στον κόμβο γονέα.
} Node;

Node* createNode(int row,int col, int g, int h) { //Συνάρτηση τύπου Node* που δημιουργεί έναν κόμβο με συγκεκριμένες παραμέτρους.
    Node* newNode = malloc(sizeof(Node)); //Δεσμεύει μνήμη για μία δομή τύπου Node
    newNode->row = row; //rows και cols καθορίζουν τις συντεταγμένες του κόμβου.
    newNode->col = col;
    newNode->g = g; //"Κόστος" από τον αρχικό κόμβο στον τρέχοντα κόμβο
    newNode->h = h; //"Κόστος" από τον τρέχοντα κόμβο στον κομβο-προορισμό
    newNode->f = g + h; //Γενική εκτίμηση για το "κόστος" από έναν κόμβο σε έναν άλλο.
    newNode->parent = NULL;
    return newNode; //Επιστρέφει έναν δείκτη στον κόμβο που δημιουργήθηκε.
}

int isValid(int **grid, int row, int col, int n) { /*Συνάρτηση που ελέγχει αν ένα σημείο του πίνακα είναι έγκυρο και μπορει να προσπελαστεί
(αν υπάρχει 0 στο σημείο εκείνο και δεν έχουν ξεπεραστεί τα όρια του πίνακα).*/
    return (row >= 0) && (row < n) && (col >= 0) && (col< n) && (grid[row][col] == 0);
}

int calculateHeuristicValue(int row, int col, int targetRow, int targetCol) { //Συνάρτηση που υπολογίζει τη τιμή heuristic, δηλαδή το κόστος από
//ένα κόμβο μέχρι τον προορισμό.
    return abs(row - targetRow) + abs(col - targetCol); //Η απόλυτη τιμή της διαφοράς της τρέχουσας γραμμής από τη γραμμή - στοχο συν
    //την απόλυτη τιμή της διαφοράς της τρέχουσας στήλης με τη στήλη - στόχο.
}

void printPath(Node* targetNode) { //Συνάρτηση που εκτυπώνει τη διαδρομή.
    if (targetNode == NULL || targetNode->parent == NULL)
        return; //Αν φτάσουμε στο τέλος σταματάει

    printPath(targetNode->parent); //Καλείται αναδρομικά

    Node* parent = targetNode->parent;
    if (parent->row == targetNode->row) { //Αν ο κόμβος που βρισκόμαστε είναι στην ίδια γραμμή με τον στόχο, τότε κινούμαστε μόνο στις στήλες
        if (parent->col < targetNode->col) //Αν ο στόχος είναι μεγαλύτερος από τον κόμβο που βρισκόματσε πάμε δεξιά,
            printf("R");
        else                               //αλλιώς αριστερά.
            printf("L");
    } else { //Αν δεν είναι στην ίδια σειρά, προσπαθούμε να τα φέρουμε κινούμενοι στις γραμμές
        if (parent->row < targetNode->row) //Αν ο στόχος βρίσκεται πάνω (δηλαδη σε μικρότερη γραμμή) παμε κάτω
            printf("D");
        else                               //αλλιώς πάνω.
            printf("U");
    }
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
                fprintf(stderr, "Invalid input for room layout\n"); //Αν δεν πληρούνται οι προυποθέσεις:
                
                for (int k = 0; k <= i; k++) { //αποδεσμεύεται η μνήμη για το κωδικοποιημένο δωμάτιο,
                    free(room[k]);
                }
                free(room);
                return 1;
            }
            room[i][j] = cell - '0'; //αλλιώς αποθηκεύεται το 0 ή το 1(σε ακέραιο αριθμό).
            //cell - '0': Μετατροπή χαρακτήρα σε ακέραιο.
        }
    }

    findPath(room, zoombaX, zoombaY, targetX, targetY, dimension);//Κλήση συνάρτησης για την εύρεση της βέλτιστης διαδρομής 

    for (int i = 0; i < dimension; i++) {//Αποδέσμευση του πίνακα για το δωμάτιο.
        free(room[i]);
    }
    free(room);

    return 0;
}