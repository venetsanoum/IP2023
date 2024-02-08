#ifndef COMPLEXLIB_H
#define COMPLEXLIB_H

typedef struct { //Struct για cpmplex αριθμό.
    double real;
    double imag;
} Complex;

Complex add(Complex a, Complex b); //Ορισμός συνάρτησης πρόσθεσης
Complex subtract(Complex a, Complex b); //Ορισμός συνάρτησης αφαίρεσης
Complex multiplication(Complex a, Complex b); //Ορισμός συνάρτησης πολλαπλασιασμού
double absolutevalue(Complex a); //Ορισμός συνάρτησης απόλυτης τιμής

#endif
