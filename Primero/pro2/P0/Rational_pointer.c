//
// Created by Miguel Fraga on 29/01/2024.
//

#include "Rational_pointer.h"
// Operacion para crear un racional
Rational createRational(int n, int d) {
    Rational temp;
    temp.num= n;
    temp.den= d;
    return temp;
}
// Operacion que retorna el numerador de un racional
int numerator(Rational r) {
    return r.num;
}
// Operacion que retorna el denominador de un racional
int denominator(Rational r) {
    return r.den;
}
// Operacion que retorna la suma de dos racionales
Rational sum(Rational r1, Rational r2) {
    Rational s;
    s.num= r1.num * r2.den + r2.num * r1.den;
    s.den= r1.den * r2.den;
    return s;
}