/*
Written by Ashutosh Vishwakarma
And Hitesh Choudhary
Date 16-04-2023
*/



#ifndef Vector_class
#define Vector_class


class Vector {
private:

    int dim;        //Dimensions in the vector

    double* vec;  //Vector

public:

    /*
    Default Constructor
    */
    Vector(){};

    /*
    Constructor
    @param dimension: Dimension
    */
    Vector(int dimension);

    /*
    Copy Constructor
    @param &vector: reference to a vector
    */
    Vector(Vector& vector);

    /*
    Takes input for the vector elements from terminal
    */
    void inputVector();

    /*
    Prints the vector elements to terminal
    */
    void printVector();

    /*
    Returns eucledian norm of the vector
    */
    double norm();

    /*
    Overload of the + operator
    */
    Vector operator +(Vector vector);


    /*
    Overload of the - operator
    */
    Vector operator -(Vector vector);

    /*
    Gives dot product
    @param vector: Second vector
    */
    double dot(Vector vector);

    /*
    Overload of * operator
    Gives scalar multiple
    */
    Vector operator* (float num);


};



class Basis {
private:
    int numVec;
    int dimVec;
    Vector* basis;
    Vector* gramSch;

public:

    /*
    Deafault constructor
    */
    Basis(){};

    /*
    Constructor
    @param l: number of vector
    @param k: dimension of vector
    */
    Basis(int l, int k);

    /*
    Prints all vectors of basis
    */
    void printBasis();

    /*
    Prints all vectors of basis
    */
    void printGramSch();

    /*
    Takes input of basis
    */
    void inputBasis();

    /*
    Updates Gram Schimdth
    */
    void updGramSch();

    /*
    Return projection coefficient for  pair (j,i) where j<i
    @param i
    @param j
    */
    float projetionCoff(int j, int i);

    /*
    Return round offed projection coefficient for  pair (j,i) where j<i
    @param i
    @param j
    */
    int rndProjetionCoff(int j, int i);
    

    /*
    Operates on basis to size reduce
    */
    void sizeReduce();


    /*
    returns true if lovasz condtion is true
    */
    bool lovasz(int i);

    /*
     reduces basis to LLL
    */
    void LLL();

};

    

#endif