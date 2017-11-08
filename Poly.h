/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Poly.h
 * Author: rezan
 *
 * Created on October 1, 2016, 8:51 PM
 */

#ifndef POLY_H
#define POLY_H

#include <iostream>

class Poly {
    
    // Console output and input operator overloads
    friend std::ostream &operator <<(std::ostream &output, const Poly &rightObj);
    friend std::istream &operator >>(std::istream &input, Poly &rightObj);
    
    
    private:
		// Representing the largest power in the polynomial.
        int largestPower;
		// Size of the Array the Polynomial is stored in.
		// At times, it may be larger than the size actually needed
		// by the Polynomial. This is because we don;t want to
		// shrink arrays only to make them grow for later use.
		// Not efficient to shrink it.
        int arraySize;
		// Array pointer representing a polynomial.
        int* coeffPtr;

        int* createNewPoly(int newArraySize);
        void initializeArrayRange(int* array, int begin, int end);
        void grow(int newLargestPower);
        
    public:
        // Constructors
        Poly();
        Poly(int coefficient);
        Poly(int coefficient, int power);
        Poly(const Poly& orig);
        virtual ~Poly();
        
        // Operator Overloads
        Poly &operator-();
        
        Poly operator +(const Poly &rightObj) const;
        Poly operator -(const Poly &rightObj) const;
        Poly operator *(const Poly &rightObj) const;
        
        // Assignment operator provides deep copy
        Poly &operator =(const Poly &rightObj);
        
        Poly &operator +=(const Poly &rightObj);
        Poly &operator -=(const Poly &rightObj);
        Poly operator *=(const Poly &rightObj);
        
        bool operator ==(const Poly &rightObj) const;
        bool operator !=(const Poly &rightObj) const;
        
        
        // Accessors and Mutators
        int getCoeff(int power) const;
        bool setCoeff(int coefficient, int power);
        
        
        
        

};

#endif /* POLY_H */

