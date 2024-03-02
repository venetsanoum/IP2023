#include <stdio.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
    return;
}

void selectionsort(int arr[], int n) {
    int i, j, min;
    for(i=0; i < n-1; i++) {
        min = i;
        for(j = i + 1; j < n; j++) { //αυξουσα σειρα
            if(arr[min] > arr[j]) 
                min = j;   //Βρίσκω τη θέση του μικρότερου στοιχείου του πίνακα
            
        }
        
    if(min != i) //Το αλλάζω με το πρώτο(και κάθε επόμενο) στοιχείο
        swap(&arr[min], &arr[i]);
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
    selectionsort(array, n);
    print(array, n);
}