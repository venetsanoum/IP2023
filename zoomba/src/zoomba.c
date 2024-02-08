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
// Συνάρτηση που θα αποδεσμεύει τις openlist και closedlist.
void freeLists(Node** openList, int** closedList, int n) {
    for (int i = 0; i < n; i++) {
        free(closedList[i]); //Αποδέσμευση μνήμης για closedlist
        free(openList[i]); //Αποδέσμευση πρώτα κάθε struct Node χωριστά.
    }
    free(closedList);
    free(openList); //Αποδέσμευση μνήμης για τον πίνακα από δείκτες
}
//Συνάρτηση για την εύρεση της βέλτιστης διαδρομής από έναν κόμβο σε έναν άλλον
void findPath(int **grid, int startX, int startY, int targetX, int targetY, int n) {

    //Έλεγχος αν τα σημεία εκκίνησης και προορισμού είναι έγκυρα.
    if (!isValid(grid, startX, startY, n) || !isValid(grid, targetX, targetY, n)) {
        printf("Invalid start or target position.\n");
        return;
    }
    //Δήλωση ανοιχτής λίστας, η οποία είναι μια λίστα προτεραιότητας και δήλωση της κλειστής λίστας όπου θα αποθηκεύονται οι κόμβοι (τα σημεία) που έχουν επισκεφθεί.
    Node** openList = malloc(n * n * sizeof(Node*)); //Ενας πίνακας από δείκτες σε δομή Node.
    int** closedList = malloc(n * sizeof(int*)); //Ενας δισδιάστατος πίνακας 

    if (openList == NULL || closedList == NULL) { //Έλεγχος επιτυχίας της δυναμικής δέσμευσης της μνήμης
        fprintf(stderr,"Memory allocation failed.\n");
        return;
    }

    for (int i = 0; i < n; i++) { //Αρχικοποίηση της κλειστής λίστας(στην αρχη όλοι οι κόμβοι είναι απροσπέλαστοι)
        closedList[i] = malloc(n * sizeof(int));
        if(!closedList[i]) {
            fprintf(stderr,"Failed to allocate memory for closed list\n");
        }
        memset(closedList[i], 0, n * sizeof(int)); //Αρχικοποίηση στο 0.
    }
    
    int openListCount = 0; //Μετρητής των θέσεων που θα επισκεφθούμε
    int H = calculateHeuristicValue(startX, startY, targetX, targetY); //Υπολογισμός της heuristic τιμης μεσω συνάρτησης
    Node* startNode = createNode(startX, startY, 0, H);
    startNode->f = startNode->g + startNode->h;

    openList[openListCount++] = startNode; //Προστίθενται ο αρχικός κόμβος

        //Κύριος βρόχος του Α* Algorithm:
    while (openListCount > 0) {//Όσο υπάρχουν ακόμα στοιχεία στην ανοιχτή λίστα
        Node* currentNode;
        currentNode = openList[0]; //Εξάγεται από τη λίστα το πρώτο στοιχείο
        int currentIndex = 0;

        for (int i = 1; i < openListCount; i++) { //Επιλέγεται ο κόμβος με τη χαμηλότερη f τιμή.Αν είναι ίσες επιλέγεται εκείνη με τη μικρότερη
        //heuristic τιμή.
            if (openList[i]->f < currentNode->f || (openList[i]->f == currentNode->f && openList[i]->h < currentNode->h)) {
                currentNode = openList[i];
                currentIndex = i;
            }
        }
        //Αφαίρεση του τρέχοντος κόμβου από την ανοιχτή λίστα
        for (int i = currentIndex; i < openListCount - 1; i++) {
            openList[i] = openList[i + 1];
        }
        openListCount--;

        int row = currentNode->row; //πάμε στην επόμενη γραμμή
        int col = currentNode->col; //πάμε στην επόμενη στήλη.
        closedList[row][col] = 1; //Ο κόμβος ελέγχθηκε.
        
        if (row == targetX && col == targetY) { //Αν έχουμε φτάσει στον επιθυμητό κόμβο εκτυπώνεται η διαδρομή.
            printPath(currentNode);
            printf("\n");
            freeLists(openList, closedList, n); //Αποδέσμευση των λιστών μεσω της συνάρτησης freeLists
            return;
        }
      
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