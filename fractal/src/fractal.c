#include <stdio.h>
#include "complexlib.h"
#include <stdlib.h>

typedef struct {
double real;
double imag;
} complex;


complex newton(complex initialpoint, double *terms, int degree){
    complex z = initialpoint;
    complex result, derivative;

}


int main(int argc, char **argv){
    if(argc != 2){ //Ελεγχος αν τα ορίσματα είναι 2.
        fprintf(stderr, "Program needs to be called as ./fractal file\n");
        return 1;
    }

    FILE* file = fopen(argv[1], "r"); //Άνοιγμα αρχείου για διάβασμα.
    if(!file) { //Έλεγχος αν άνοιξε το αρχείο.
        fprintf(stderr, "Faile to open file\n");
        return 1;
    }

    int degree; //Ο βαθμός του πολυωνύμου.
    if(fscanf(file, "%d",  &degree) != 1){ //Διάβασμα και έλεγχος ότι είναι 1.
        fprintf(stderr, "Degree of the polyonimal could not be detected\n");
        return 1;
    }

    double *terms; //Πίνακας που θα αποθηκεύσει τους όρους του πολυωνύμου.
    terms = malloc((degree + 1) * sizeof(double)); //Δυναμική δέσμευση μνήμης με προσθήκη +1 για τον σταθερό όρο
    if(!terms) { //Έλεγχος επιτυχίας της malloc
        fprintf(stderr, "Failed to allocate memory\n");
        return 1;
    }  

    int i;
    for(i = 0; i < degree + 1; i++){
        double number;
        if(fscanf(file,"%lf", &number) != 1){ //Διάβασμα των όρων από το αρχείο και τοποθέτηση στον πίνακα terms[].
            fprintf(stderr, "Failed to read polyonimal's terms\n");
            return 1;
        }
        terms[i] = number;
    }  
    

    double minreal, minimag, maxreal, maximag, step;

    if(fscanf(file, "%lf %lf %lf %lf %lf", &minreal, &minimag, &maxreal, &maximag, &step) != 5){
        fprintf(stderr, "Error reading data\n"); //Διάβασμα των δεδομένων για τη δημιουργία του παραθύρου και τον καθορισμό του step.
        return 1;
    }

    /*complex initialGuess; //Αρχική εκτίμηση για τη ρίζα ώστε να λειτουργήσει η μέθοδος newton
    initialGuess.real = 0.0;
    initialGuess.imag = 0.0;*/

    complex **roots; //Πίνακας που θα αποθηκεύσει τις ρίζες
    int realsteps = (int)((maxreal - minreal) / step); //Ο αριθμός των βημάτων που χρειάζεται από το minreal εως το maxreal.

    roots = malloc(realsteps * sizeof(complex *));
    if(!roots) {
        fprintf(stderr, "Failed to allocate memory\n");
        return 1;
    }

    int imagsteps = (int)((maximag - minimag) / step); //Ο αριθμός των βημάτων που χρειάζεται από το minimag εως το maximag.

    for (int i = 0; i < realsteps; i++) {
        roots[i] = malloc(imagsteps * sizeof(complex));
        if(!roots[i]) {
            fprintf(stderr, "Failed to allocate memory\n");
            free(roots);
            return 1;

        }
    }
    
    int rows = 0;
    int cols = 0;
    for (double realPart = minreal; realPart <= maxreal; realPart += step) {
        cols = 0;
        for (double imagPart = minimag; imagPart <= maximag; imagPart += step) {
            complex point;
            point.real = realPart;
            point.imag = imagPart;

            complex root = newton(point, terms, degree);

            roots[rows][cols] = root;
            ++cols;

        }
        ++rows;
    }


    fclose(file);
    free(terms);
    return 0;

}