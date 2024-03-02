#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>

void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
    return;
}
void bubblesortopt(int array[], int n) {
    int i,j;
    bool flag;
    for(i=0; i < n-1; i++) {
        flag = false;
        for(j=0; j < n - i - 1; j++) {
            if(array[j] > array[j+1]) { //αυξουσα σειρά
                swap(&array[j], &array[j+1]);
                flag = true;
            }
        }
        // If no two elements were swapped by inner loop,
        // then break
        if(flag==false) {
            break;
        }
    }

}
void bubblesort(int array[], int n) {
    /*Πάω από αριστερά προς δεξιά και ελέγχω γειτονικά στοιχεία και το μεγαλύτερο πάει δεξιά. 
Αρα αρχικά το μεγαλύτερο πάει πιο δεξιά απο όλα. 
Συνεχίζω βρίσκοντας το 2ο μεγαλύτερο στοιχείο κοκ μέχρι να ταξινομηθεί ο πίνακας.*/
    int i,j;
    for(i=0; i<n-1; i++) {
        for(j=n-1; j>=1; j--) {
            if(array[j] < array[j-1]) { //αυξουσα σειρά
                swap(&array[j], &array[j-1]); //ανταλλαγή γειτονικών στοιχείων αν είναι σε λάθος σειρά.σ
            }
        }
    }
}

void print(int arr[], int n) {
    for(int i = 0; i< n; i++) {
        printf("%d ", arr[i]);
    }

}

int main() {
    int array[] = {64, 25, 12, 22, 11};
    int n = sizeof(array)/sizeof(int);
    bubblesort(array, n);
    print(array, n);
}