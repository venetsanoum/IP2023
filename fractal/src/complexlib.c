#include "complexlib.h"
#include <math.h>

Complex add(Complex a, Complex b) { //Πρόσθεση
    Complex result;
    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;
    return result;
}

Complex subtract(Complex a, Complex b) { //Αφαίρεση
    Complex result;
    result.real = a.real - b.real;
    result.imag = a.imag - b.imag;
    return result;
}

Complex multiplication(Complex a, Complex b) { //Πολλαπλασιασμός
    Complex result;
    result.real = (a.real * b.real) - (a.imag * b.imag);
    result.imag = (a.imag * b.imag) + (a.real * b.real);
    return result;
}

double absolutevalue(Complex a) { //Απόλυτη τιμή
    return sqrt(a.real * a.real + a.imag * a.imag);
}
