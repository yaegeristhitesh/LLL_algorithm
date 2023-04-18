/*
Written by Ashutosh Vishwakarma
And Hitesh Choudhary
Date 16-04-2023
*/


#include "Vector_class.h"
#include <iostream>
#include <math.h>

Vector::Vector(int dimension)
{
    this->dim = dimension;
    this->vec = new double[dimension];
}

Vector::Vector(Vector& vector)
{
    this->dim = vector.dim;
    this->vec = new double[dim];

    for (int i=0; i < this->dim; i++) { this->vec[i] = vector.vec[i]; }
}

void Vector::inputVector()
{
    for (int i=0; i < this->dim; i++) {
        std::cin >> this->vec[i];
    }
}

void Vector::printVector()
{
    std::cout << "(";
    for (int i=0; i < this->dim; i++) {
        std::cout << this->vec[i] ;
        if(i<this->dim-1)std::cout<<", ";
    }
    std::cout << ")\n";
}

double Vector::norm()
{
    double sqrSum = 0;
    for (int i=0; i < this->dim; i++) { sqrSum += pow(this->vec[i], 2); }
    return sqrt(sqrSum);
}

Vector Vector::operator+(Vector vector)
{
    if (this->dim != vector.dim) { Vector ref; return ref; }
    Vector newVector(this->dim);
    for (int i=0; i < this->dim; i++) {
        newVector.vec[i] = this->vec[i] + vector.vec[i];
    }
    return newVector;
}

Vector Vector::operator-(Vector vector)
{
    if (this->dim != vector.dim) { Vector ref; return ref; }
    Vector newVector(this->dim);
    for (int i=0; i < this->dim; i++) {
        newVector.vec[i] = this->vec[i] - vector.vec[i];
    }
    return newVector;
}

double Vector::dot(Vector vector)
{
    double dotPrd=0;
    for (int i=0; i < this->dim; i++) {
        dotPrd += this->vec[i] * vector.vec[i];
    }
    return dotPrd;
}

Vector Vector::operator*(float num)
{   
    Vector mult(this->dim);
    for (int i=0; i < this->dim; i++) {
        mult.vec[i] = num * this->vec[i];
    }
    return mult;
}


Basis::Basis(int l, int k)
{
    this->numVec = l;
    this->dimVec = k;
    this->basis = new Vector[numVec];
    this->gramSch = new Vector[numVec];

    

    for (int i=0; i < numVec; i++) {
       Vector temp1(dimVec);
       Vector temp2(dimVec);
       this->basis[i] = temp1;
       this->gramSch[i] = temp2;
    }
}

void Basis::printBasis()
{
    std::cout << '{';
    for (int i=0; i < this->numVec; i++) {
        this->basis[i].printVector();
        //if (i < this->numVec - 1) std::cout << ", ";
    }
    std::cout << "}\n";
}

void Basis::printGramSch()
{
    std::cout << '{';
    for (int i=0; i < this->numVec; i++) {
        this->gramSch[i].printVector();
        if (i < this->numVec - 1) std::cout << ", ";
    }
    std::cout << "}\n";
}

void Basis::inputBasis()
{
    for (int i=0; i < this->numVec; i++) {
        this->basis[i].inputVector();
    }

}

void Basis::updGramSch()
{
    this->gramSch[0] = this->basis[0];
    for (int i=1; i < this->numVec; i++) {
        this->gramSch[i] = this->basis[i];

        Vector summation(this->dimVec);     //summation of vectors with their projection coefficients
        summation = summation - summation;  //to set all component to zero
        for (int j=0; j < i; j++) {
            float uji = projetionCoff(j, i);
            
            Vector *temp = new Vector;

            *temp = this->gramSch[j] * uji;
            summation = summation + *temp;

            delete(temp);
        }
        this->gramSch[i] = this->gramSch[i] - summation;
    }
}

float Basis::projetionCoff(int j, int i)
{
    float temp = (this->basis[i].dot(this->gramSch[j])) / (pow(this->gramSch[j].norm(), 2));
        return temp;
}

int Basis::rndProjetionCoff(int j, int i)
{   
    float x = projetionCoff(j, i);
    int gif = x;
    if (x < 0 && gif!=x) gif--;
    if (gif + 0.5 < x) return gif + 1;
    return gif;
}

void Basis::sizeReduce()
{
    this->updGramSch();
    for (int i=1; i < this->numVec; i++) {

        Vector summation(this->dimVec);     //summation of vectors with their projection coefficients
        summation = summation - summation;  //to set all component to zero
        for (int j=0; j < i; j++) {
            float uji = rndProjetionCoff(j, i);

            Vector* temp = new Vector;

            *temp = this->basis[j] * uji;
            summation = summation + *temp;
            delete(temp);
        }
        this->basis[i] = this->basis[i] - summation;

    }
}

bool Basis::lovasz(int i)
{
    
    return (3.0/4-(pow(this->projetionCoff(i,i+1),2)))*(pow(this->basis[i].norm(),2))<=(pow(this->basis[i+1].norm(),2));
}

void Basis::LLL()
{
    this->sizeReduce();
    for (int i=0; i < this->numVec - 1; i++) {
        if (!this->lovasz(i)) {
            Vector temp = this->basis[i];
            this->basis[i] = this->basis[i + 1];
            this->basis[i + 1] = temp;
            this->LLL();
            break;
        }
    }
    std::cout << "Successfully executed." << std::endl;
}
