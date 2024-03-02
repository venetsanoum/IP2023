/*Insertion sort is a simple sorting algorithm that works similar to the way you sort playing cards in your hands. 
The array is virtually split into a sorted and an unsorted part. Values from the unsorted 
part are picked and placed at the correct position in the sorted part.*/
#include <stdio.h>
#include <stdlib.h> 

void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
    return;

}
void insertionsort(int array[], int n) { 
    int i,j;

    for(i=1; i<=n-1; i++) {  //Ελέγχω γειτονικά στοιχεία και τα ανταλλάσσω αν χρειάζεται:
    // 12 11 13 5: 
        //i) Ελέγχω 12 11 και κάνω swap: 11 12 13 5 
        //ii) Ελέγχω 12 13 --> Ελέγχω 11 12.
        //iii) Ελέγχω 13 5 --> (11 12 5 13) --> ελέγχω 12 5 --> (11 5 12 13) --> ελέγχω 5 11 --> (5 11 12 13)          
        j = i-1;
        while(j>=0 && array[j] > array[j+1]) { //αυξουσα σειρα
            swap(&array[j], &array[j+1]);
            j--;
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
    insertionsort(array, n);
    print(array, n);
}