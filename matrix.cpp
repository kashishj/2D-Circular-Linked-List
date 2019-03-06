/*
 * todo.cpp
 * Contains the member function's implementation of the class Matrix
 */

#include "matrix.h"

/*
 * Helper function called by constructor to complete circular links and initialize class data members inside matrix
 */
Element* rowMatrix (int width, int startId){
    // create the head of the circular linked list
    Element* head = new Element{nullptr, nullptr, nullptr, nullptr, startId}; // head points to first node Element with startId
    head->left = head->right = head;
    
    // max id boundary to change id
    int boundary = startId + width;
    
    // create the remaining nodes (including tail) of the linked list
    Element* temp = head;
    for (int i = startId + 1; i< boundary; i++,temp = temp ->right){
        Element* newNode = new Element{nullptr, nullptr, temp, nullptr, i}; // nodes with id updated
        temp->right = newNode; // complete inner links
    }
    
    // complete the circular links of the head and tail
    temp->right = head;
    head->left = temp;
    
    return head;
}

/*
 * Constructor of the Matrix class
 */
Matrix::Matrix(int height, int width){
    this->height = height;
    this->width = width;
    int startingId = 1; // first node (row 0, col 0) has id 1
    
    for (int i = 0; i < height; i++){
        rowHeads[i] = rowMatrix(width,startingId);
        startingId += width;// update startingId for the node at each row (col 0) to send to rowMatrix function
    }
    // link colHeads to the first row through temp pointer of type Element
    Element* temp = rowHeads[0];
    for (int i = 0; i < width; i++){
        colHeads[i] = temp; // point at first cell Element of row 0
        temp = temp -> right;
    }
    
    // Special case when height of matrix is 1
    if (height == 1){
        for (int i = 0; i < width; i++){
            colHeads[i]->up = colHeads[i];
            colHeads[i]->down = colHeads[i];
        }
    }
    
    // Complete links in between the matrix
    int i = 0;
    while(i < width){
        Element* columnNode = colHeads[i];
        int j = 1;
        while(j < height){
            Element* rowNode = rowHeads[j];
            
            for(int right = 0; right < i; right++, rowNode = rowNode->right);
            columnNode->down = rowNode;
            rowNode->up = columnNode;
            columnNode = columnNode->down;
            // Special case if j reaches max the max height, complete the circular links up and down
            if(j == height-1)
            {
                columnNode->down = colHeads[i];
                colHeads[i]->up = columnNode;
            }
            j = j+1;
        }
        i = i+1;
    }
    
}

/*
 * isReverse() of the Matrix class
 */
bool Matrix::isReverse() const{
    // if the matrix is in reverse, the id at row 0 col 0 should be height*width
    for (int i = 0; i < width; i++){
        if(rowHeads[0]->id != height*width){
            return false;
        }
    }
    // check if the id is in descending order going across the matrix from left to right, row-by-row
    for (int j = 0; j < height; j++){
        for (Element* p = rowHeads[j]; p!= rowHeads[j]->left;p=p->right)
            if (!(p->id > p->right->id)){
                return false;
            }
        
    }
    
    int correctComparisons = 0;
    for (int i = 0; i < height; i++){
        Element* temp = rowHeads[i];
        Element* temp2 = temp->down;
        if (temp2->id == ((temp->id)-width)){
            correctComparisons+=1;
        }
        if (correctComparisons != height-1){
            return false;
        }
    }
    
    return true;
}
/*
 * reverseRow() of the Matrix class
 */
void Matrix::reverseRow(int row){
    
    Element* firstNode = rowHeads[row];
    Element* lastNode = rowHeads[row]->left;
    // until it reaches the middle:
    // odd number of columns, middle not counted as the connections are the same
    // even number of columns, stops at last two in the middle, and does not continue going forward respectively
    for (; firstNode->id<lastNode->id; firstNode = firstNode->right,lastNode = lastNode->left){
        // link up:
        Element* temp = firstNode->up;
        firstNode->up->down = lastNode;
        lastNode->up->down = firstNode;
        firstNode->up = lastNode->up;
        lastNode->up = temp;
        
        // link down:
        temp = firstNode->down;
        firstNode->down->up = lastNode;
        lastNode->down->up = firstNode;
        firstNode->down = lastNode->down;
        lastNode->down = temp;
        
    }
    // reverse the row elements
    Element* p = rowHeads[row];
    
    Element* currentNode,* nextNode,* tempNode;
    currentNode = p;
    do{
        nextNode = currentNode ->right;
        tempNode = currentNode ->left;
        currentNode ->left = currentNode->right;
        currentNode->right= tempNode;
        currentNode = nextNode;
    }while(currentNode !=p);
    rowHeads[row]=rowHeads[row]->right;
    
    
    // Special case when it is row number is the first row
    if (row == 0){
        Element* r = colHeads[0];
        Element* h = r->right;
        for (int i = 0; i< width; i++){
            colHeads[i]=h;
            h = h->right;
        }
    }
    
}


/*
 * circularShift() member function of the Matrix class
 * Updates the links for the circular linked list when an operation is peformed on a matrix
 */
void Matrix::circularShift(direction d, int index){
    
    Element* temp = nullptr;
    
    if (d == LEFT || d == RIGHT){
        temp = rowHeads[index];
        if (d == LEFT){
            rowHeads[index] = temp->right;
            
            // fix the down pointers of row rowHeads[index] and the up pointers of rowHeads[index+1]
            Element* current = rowHeads[index];
            Element* prev = rowHeads[index]->left;
            Element* lastDown = prev->down;
            for (int i = 0; i < width; i++){
                current->down = lastDown;
                lastDown->up = current;
                current = current->right;
                lastDown = lastDown->right;
            }
            Element* lastUp = prev->up;
            for (int i = 0; i < width; i++){
                current->up = lastUp;
                lastUp->down = current;
                current = current->right;
                lastUp = lastUp->right;
            }
        }
        if (index == 0 && d == LEFT){
            Element* r = colHeads[0];
            Element* h = r->right;
            for (int i = 0; i< width; i++){
                colHeads[i]=h;
                h = h->right;
            }
        }
        if (d == RIGHT){
            rowHeads[index] = temp->left;
            Element* current = rowHeads[index];
            Element* prev = rowHeads[index]->right;
            Element* lastDown = prev->down;
            for (int i = 0; i < width; i++){
                current->down = lastDown;
                lastDown->up = current;
                current = current->right;
                lastDown = lastDown->right;
            }
            Element *lastup = prev->up;
            for (int i = 0; i < width; i++){
                current->up = lastup;
                lastup->down = current;
                current = current->right;
                lastup = lastup->right;
            }
            
        }
        if (index == 0 && d == RIGHT){
            Element* r = colHeads[0];
            Element* h = r->left;
            for (int i = 0; i< width; i++){
                colHeads[i]=h;
                h = h->right;
            }
        }
    }
    if (d == UP || d == DOWN){
        temp = colHeads[index];
        if (d == UP){
            colHeads[index] = temp->down;
            Element *current = colHeads[index];
            Element *prev = colHeads[index]->up;
            Element *lastright = prev->right;
            for (int i = 0; i < height; i++){
                current -> right = lastright;
                lastright->left = current;
                current = current->down;
                lastright = lastright->down;
            }
            Element *lastleft = prev->left;
            for (int i = 0; i < height; i++){
                current->left = lastleft;
                lastleft->right = current;
                current = current->down;
                lastleft = lastleft->down;
            }
        }
        
        if (index == 0 && d == UP){
            Element* c = rowHeads[0];
            Element* h = c->down;
            for (int i = 0; i< height; i++){
                rowHeads[i]=h;
                h = h->down;
            }
        }
        if (d == DOWN){
            colHeads[index] = temp->up;
            Element *current = colHeads[index];
            Element *prev = colHeads[index]->down;
            Element* lastRight = prev->right;
            for (int i = 0; i < height; i++){
                current -> right = lastRight;
                lastRight->left = current;
                current = current->down;
                lastRight = lastRight->down;
            }
            Element* lastLeft = prev->left;
            for (int i = 0; i < height; i++){
                current->left = lastLeft;
                lastLeft->right = current;
                current = current->down;
                lastLeft = lastLeft->down;
            }
        }
        if (index == 0 && d == DOWN){
            Element* c = rowHeads[0];
            Element* h = c->up;
            for (int i = 0; i< height; i++){
                rowHeads[i]=h;
                h = h->down;
            }
        }
    }
    
}
/*
 * Print the matrix
 */
void Matrix::print() const {
    const Element* current;
    for (int i = 0; i < height; i++) { // go through each row, create a current pointer pointing at each rowHeads
        cout << "|\t";
        current = rowHeads[i];
        for (int j = 0; j < width; j++) { // for each row, go through each col
            cout << current->id << "\t"; // print the id for the cell current is pointing at
            current = current->right; // keep moving forward, point at next cell
        }
        cout << "|" << endl;
    }
    cout << endl;
}
/*
 * Destructor of the Matrix class
 */
Matrix::~Matrix(){
    for (int i = 0; i < height; i++){
        if (rowHeads[i] == nullptr) return;
        Element *next;
        for (Element *current = rowHeads[i]->right; current != rowHeads[i]; current = next){
            next = current ->right;
            delete current;
        }
        delete rowHeads[i];
        rowHeads[i] = nullptr;
    }
}






