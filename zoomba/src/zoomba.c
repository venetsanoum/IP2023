#include <stdio.h>
#include <stdlib.h>

typedef struct Node { //Αυτοαναφορική δομή Node
    int row, col; //Συντεταγμένες του κόμβου στο δωμάτιο
    struct Node* parent; //Δείκτης στον κόμβο γονέα.
} Node;
// Συνάρτηση που δημιουργεί νέους κόμβους
Node* createNode(int row, int col, Node* parent) {
    Node* newNode = malloc(sizeof(Node)); //Δυναμική δέσμυεση μνήμης για μια δομή Node.
    if (!newNode) { //Έλγεχος επιτυχίας της malloc
        fprintf(stderr, "Failed to allocate memory for new node\n");
        exit(1);
    }
    newNode->row = row; //Αρχικοποιούνται τα μέλη του
    newNode->col = col;
    newNode->parent = parent;
    return newNode;
}

int isValid(int **grid, int row, int col, int n) { /*Συνάρτηση που ελέγχει αν ένα σημείο του πίνακα είναι έγκυρο και μπορει να προσπελαστεί
(αν υπάρχει 0 στο σημείο εκείνο και δεν έχουν ξεπεραστεί τα όρια του πίνακα).*/
    return (row >= 0) && (row < n) && (col >= 0) && (col< n) && (grid[row][col] == 0);
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
    return; //Η συνάρτηση επιστρέφει για την εκτύπωση της επόμενης κίνησης.
}
//Συνάρτηση που αποδεσμεύει χώρο για την ουρά και τον πίνακα που δημιουργήθηκαν
void freefun(Node** queue, int** visited, int n) {
    for (int i = 0; i < n; i++) {
        free(visited[i]); //Αποδέσμευση μνήμης για closedlist
    }
    free(visited);
    free(queue); //Αποδέσμευση μνήμης για τον πίνακα από δείκτες
}
//Συνάρτηση που αποδεσμεύει τη μνήμη που δεσμεύτηκε για κάθε κόμβο
void freeNodes(Node* current) {
    if(current == NULL) 
        return;
    
    freeNodes(current->parent); //Καλείται αναδρομικά 
    free(current); //και απελευθερώνεται η μνήμη για κάθε κόμβο
    return;
}

//Συνάρτηση για την εύρεση της βέλτιστης διαδρομής από έναν κόμβο σε έναν άλλον
void BFS(int **grid, int startX, int startY, int targetX, int targetY, int n) {
    int **visited = malloc(n * sizeof(int*)); //Δημιουργία δισδιάστατου πίνακα που θα αντιστοιχεί στον πίνακα του δωματίου
    // και θα έχει 0 όταν το σημείο δεν έχει ελεγχθεί και 1 όταν ελεγχθεί.
    if (!visited) { //Έλγεχος επιτυχίας της malloc.
        fprintf(stderr, "Failed to allocate memory for visited array\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        visited[i] = calloc(n, n * sizeof(int)); //Calloc μιας και αρχικά θέλουμε όλα τα στοιχεία να είναι 0.
        if (!visited[i]) { //Έλεγχος επιτυχίας της calloc
            fprintf(stderr, "Failed to allocate memory for visited array\n");
            free(visited);
            exit(1);
        }
    }

    Node** queue = malloc(n * n * sizeof(Node*)); //Δημιουργείται ένας πίνακας από δείκτες σε δομές Node (αποτελεί μία ουρά).
    if(!queue) { //Έλεγχος επιτυχίας της malloc.
        fprintf(stderr, "Failed to allocate memory for queue\n");
        exit(1);
    }
    int front = 0, rear = 0; //Τα βασικά στοιχεία μιας ουράς (η αρχή και το τέλος)

    visited[startX][startY] = 1; //Ο πρώτος κόμβος έχει επισκεφθεί
    queue[rear++] = createNode(startX, startY, NULL); //Προστίθενται ο αρχικός κόμβος στο τέλος της ουράς.

    while (front != rear) { //Όσο δεν έχει αδειάσει η ουρά.
        Node* current = queue[front++]; //Εξάγεται το πρώτο στοιχείο από την ουρά (αποτελεί τον τρέχοντα κόμβο)
        int row = current->row; //Κρατούνται οι συντεταγμένες του (γραμμές και στήλες)
        int col = current->col;
    
        if (row == targetX && col == targetY) { //Αν έχουμε φτάσει στο επιθυμητό σημείο:
            printPath(current); //εκτυπώνεται το μονοπάτι
            printf("\n");
            freeNodes(current); //αποδεσμεύεται η μνήμη για κάθε κόμβο που δημιουργήθηκε
            freefun(queue, visited,n); //αποδεσμεύεται η μνήμη για την ουρά και τον πίνακα των επισκέψεων
            return;
        }

        //Οι 4 θέσεις των δύο πινάκων αφορούν αριστερά, πάνω, κάτω, δεξιά.
        int rowMoves[] = { -1, 0, 0, 1 }; //Στις γραμμές κινούμαστε αριστερά και δεξιά
        int colMoves[] = { 0, -1, 1, 0 }; //Στις στήλες κινούμαστε πάνω και κάτω

        for (int i = 0; i < 4; i++) { //Γίνονται οι κινήσεις. Πρώτα αριστερά και οι στήλες δεν μεταβάλλονται κοκ.
            int newRow = row + rowMoves[i];
            int newCol = col + colMoves[i];

            if (isValid(grid, newRow, newCol, n) && !visited[newRow][newCol]) { //Αν το σημείο είναι έγκυρο και δεν έχει ελεγχθεί:
                visited[newRow][newCol] = 1; //Ενημερώνεται η κατάσταση του στον πίνακα visited[]
                queue[rear++] = createNode(newRow, newCol, current); //και πτοστίθεται στο τέλος της ουράς (και γονέα τον τρέχοντα κόμβο)
            }
        }
    }
    printf("0\n"); //Αν δεν βρέθηκε μονοπάτι τυπώνεται 0.
    freefun(queue, visited, n); // και αποδεσμεύεται η μνήμη που δεσμεύτηκε.
    return;
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
    if(!room) { // Έλεγχος επιτυχίας της malloc
        fprintf(stderr, "Failed to allocate memory\n");
        return 1;
    }

    for (int i = 0; i < dimension; i++) {
        room[i] = malloc(dimension * sizeof(int));
        if(!room[i]) { // Έλεγχος επιτυχίας της malloc
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

    BFS(room, zoombaX, zoombaY, targetX, targetY, dimension);//Κλήση συνάρτησης για την εύρεση της βέλτιστης διαδρομής 

    for (int i = 0; i < dimension; i++) {//Αποδέσμευση του πίνακα για το δωμάτιο.
        free(room[i]);
    }
    free(room);

    return 0;
}