/*
 * main.cpp
 * The driver program to test the program
 */
//  Created by Kashish Jagtiani on 01/12/18.


//--------------------------------------------------------------------------------------------------------------------------------//
//                                                          NOTES AND ASSUMPTIONS:
// - Build an m-by-n (row-by-column) matrix to manipulate its data (max size: 8-by-8)
// - The numbers (data) inside the matrix will be referred to as "id"
// - Throughout the project, we count the rows and columns from the index 0 onwards as a programming convention.

// - Note: When building the matrix, the numbers inside the matrix are arranged in ascending order, starting from 1. Example of an 2x3 matrix is shown below:
//       Col 0   Col 1   Col 2
// Row 0    1      2       3
// Row 1    4      5       6
// - The program stops when your matrix data is descending order, i.e. the matrix is in in reverse-order. Example of a descending 2x3 matrix is shown below:
//       Col 0   Col 1   Col 2
// Row 0    6      5       4
// Row 1    3      2       1
// - Operations available to manipulate the data in the matrix:
// 1. Right Circular Shift: A particular row of a matrix performs a circular shift to the right by one cell.
// 2. Left Circular Shift: A particular row of a matrix performs a circular shift to the left by one cell.
// 3. Up Circular Shift: A particular column of a matrix performs a circular shift upward by one cell.
// 4. Down Circular Shift: A particular column of a matrix performs a circular shift downward by one cell.
// 5. Reverse Row: A particular row of a matrix is flipped.

#include "matrix.h"
int main() {
    {
        cout << endl <<
        "=======================" << endl <<
        "Build your m-by-n matrix" << endl <<
        "=======================" << endl;
        int m, n;
        do {
            cout << "Enter m(row) and n(col), with a space in between, to build your matrix : ";
            
            cin >> m;
            cin >> n;
        } while (m < 1 || n < 1 || m > MAX_SIZE || n > MAX_SIZE);
        
        // Build a Matrix object called 'a' with dimensions m-by-n:
        Matrix a(m, n);
        a.print();
        
        char input1, input2;
        do {
            do{
            cout << "Input any of the following operations (1-5) of your choice to manipulate data in the matrix:" << endl <<
            "1: Up Circular Shift" << endl <<
            "2: Down Circular Shift" << endl <<
            "3: Left Circular Shift" << endl <<
            "4: Right Circular Shift" << endl <<
            "5: Reverse Row." << endl;
            cout << "Enter (1-5) only: ";
            cin >> input1;
                cout << endl;
            } while (input1 < '1' || input1 > '5');
            
            cin.ignore();
            switch(input1){
                case '1': cout << "Enter which column of your matrix to perform Up Circular Shift (Note: Enter valid column number): "; break;
                case '2': cout << "Enter which column of your matrix to perform Down Circular Shift (Note: Enter valid column number): "; break;
                case '3': cout << "Enter which row of your matrix to perform Left Circular Shift (Note: Enter valid row number): "; break;
                case '4': cout << "Enter which row of your matrix to perform Right Circular Shift (Note: Enter valid row number): "; break;
                case '5': cout << "Enter which row of your matrix to perform Reverse Row (Note: Enter valid row number): "; break;
            }
            
            cin >> input2;
            cin.ignore();
            if (input1 >= '1' && input1 <= '4' )
                a.circularShift(static_cast<direction>(input1 - '1'), input2 - '0');
            if (input1 == '5')
                a.reverseRow(input2 - '0');
            a.print();
        } while (!a.isReverse()); // the program stops when the matrix is in descending order.
    }
    cout << "All objects have been destructed. "<< endl;
}
