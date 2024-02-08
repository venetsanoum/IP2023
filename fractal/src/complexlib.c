#include <math.h>

typedef struct {
double real;
double imag;
} complex;

complex n;
complex add (complex a, complex b) {
    n.real = a.real + b.real;
    n.imag = a.imag + b.imag;
    return n;
}

complex substarction(complex a, complex b) {
    n.real = a.real - b.real;
    n.imag = a.imag - b.imag;
    return n;
}

complex multiplication(complex a, complex b) {
    n.real = (a.real * b.real) - (a.imag * b.imag);
    n.imag = (a.imag * b.imag) + (a.real * b.real);
    return n;
}

double absolutevalue(complex a) {
    return  sqrt(a.real * a.real + a.imag * a.imag);

}