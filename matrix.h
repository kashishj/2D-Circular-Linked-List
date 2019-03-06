/*
 * matrix.h
 * Contains the Class definition to create Matrix objects and other data type including Structure and Enumeration
 */


#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>

using namespace std;

const int MAX_SIZE = 8;
enum direction {UP, DOWN, LEFT, RIGHT};


/*
 * Each cell in the matrix is represented by a struct data type Element with 4 pointers
 */
struct Element {
    Element* up;    // To link to the Element on the same col in the above row. If this Element is in the top row (Row 0), it links to the Element on Row (m-1)
    Element* down;  // Similar to up but it is to link to the Element in the row below.
    Element* left;  // To link to the Element on the left.
    Element* right; // To link to the Element on the right.
    const int id; // the number inside each matrix 
};

/*
 * Class definition to build a Matrix object:
 */
class Matrix {
    private:
	int width;      // The width of the matrix
	int height;		// The height of the matrix
	Element* rowHeads[MAX_SIZE];
	Element* colHeads[MAX_SIZE];
    public:

	/**
	 * The constructor of the class. Given the width and height of the matrix, it should construct a height-by-width matrix in ascending
     * order.
	 */
	Matrix(int height, int width);
	/**
	 * Destructor of the class
	 */
	~Matrix();

	/**
	 * To perform a "reverse row" operation. The parameter indicates the row number that to be reversed.
	 */
	void reverseRow(int);

	/**
	 * To perform a "circular shift" operation.
	 * The first parameter is of the enumeration type, direction. Possible values: RIGHT, LEFT, UP, DOWN
	 * For example, if it is RIGHT, it means to perform a "right circular shift".
	 * The second parameter is the row number or the col number for the operation.
	 */
	void circularShift(direction, int);

	/**
	 * To check if the matrix is in reverse-order to end the program. Returns true if it is, otherwise returns false.
	 */
	bool isReverse() const;

	/**
	 *  This function prints the matrix.
	 */
	void print() const;
	/**
	 *  This function is to check the matrix links.
	 */
	void debug() const;

};



#endif

