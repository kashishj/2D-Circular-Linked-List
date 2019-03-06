/*
 * helper.cpp
 * Contains helper functions for debugging purposes, including member function void Matrix::debug() const;
 */

#include "matrix.h"

/* A helper function to be used in class Matrix member function, debug() :
 *  Given a pointer to an Element, check if it is a circular linked list by traversing in a particular direction (Up, Down, Left, Right).
 */
bool check(const Element* list, direction dir, bool debug = true) {
    const Element* current = list;
    do {
	cout << current->id << " ";
	switch (dir) {
	    case UP:	current = current->up; break;
	    case DOWN:  current = current->down; break;
	    case LEFT:  current = current->left; break;
	    case RIGHT: current = current->right; break;
	}
    } while (current != list && current != nullptr);

    if (debug) {
	if (current == nullptr)
	    cout << "\t\tIt is not circular" << endl;
	else
	    cout << "\t\tIt is circular" << endl;
    }
    return current != nullptr;
}



// Check the Matrix object links
void Matrix::debug() const {
    cout << "Traverse right" << endl;
    for (int i = 0; i < height; i++) {
	cout << "Row " << i << "\t";
	if (!check(rowHeads[i], RIGHT))
	    cout << "Row " << i << " is not a circular linked list (right pointer)." << endl;
    }
    cout << "Traverse left" << endl;
    for (int i = 0; i < height; i++) {
	cout << "Row " << i << "\t";
	if (!check(rowHeads[i], LEFT))
	    cout << "Row " << i << " is not a circular linked list (left pointer)." << endl;

    }
    cout << "Traverse down" << endl;
    for (int i = 0; i < width; i++) {
	cout << "Col " << i << "\t";
	if (!check(colHeads[i], DOWN))
	    cout << "Col " << i << " is not a circular linked list (down pointer)." << endl;


    }
    cout << "Traverse up" << endl;
    for (int i = 0; i < width; i++) {
	cout << "Col " << i << "\t";
	if (!check(colHeads[i], UP))
	    cout << "Col " << i << " is not a circular linked list (up pointer)." << endl;

    }
}


