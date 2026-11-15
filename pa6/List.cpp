/***
* Peter Liang
* xliang41
* 2024 Fall CSE 101 PA5
* List.cpp
* Implementation file for List ADT.
***/


#include <stdexcept>

#include "List.h"

using namespace std;


// Node constructor.
List::Node::Node(ListElement x){
    data = x;
    next = nullptr;
    prev = nullptr;
}

// Creates new List in the empty state.
List::List(){
    frontDummy = new Node(0);
    backDummy = new Node(0);
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
}

// Copy constructor.
List::List(const List& L){
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
    Node *N = L.frontDummy->next;
    while (N != L.backDummy){
        this->insertAfter(N->data);
        moveNext();
        N = N->next;
    }
    moveFront();
}

// Destructor.
List::~List(){
    clear();
    delete frontDummy;
    delete backDummy;
}


// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const{
    return num_elements;
}

// front()
// Returns the front element in this List. Pre: length()>0.
ListElement List::front() const{
    if (length() <= 0){
        throw length_error("List: front(): empty list.");
    }
    return frontDummy->next->data;
}

// back()
// Returns the back element in this List. Pre: length()>0.
ListElement List::back() const{
    if(length() <= 0){
        throw length_error("List: back(): empty list.");
    }
    return backDummy->prev->data;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
    if ((pos_cursor<0) || (pos_cursor>length())){
        throw range_error("List: position(): cursor out of range.");
    }
    return pos_cursor;
}

// peekNext()
// Returns the element after the cursor. Pre: position()<length().
ListElement List::peekNext() const{
    if (pos_cursor >= length()){
        throw range_error("List: peekNext(): cursor out of range.");
    }
    return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor. Pre: position()>0.
ListElement List::peekPrev() const{
    if (pos_cursor <= 0){
        throw range_error("List: peekPrec(): cursor our of range.");
    }
    return beforeCursor->data;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
    moveFront();
    while (length() > 0){
        eraseAfter();
    }
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
    afterCursor = backDummy;
    beforeCursor = afterCursor->prev;
    pos_cursor = num_elements;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over.
// Pre: position()<length().
ListElement List::moveNext(){
    if (pos_cursor > length()){
        throw range_error("List: moveNext(): cursor our of range.");
    }
    beforeCursor = beforeCursor->next;
    afterCursor = afterCursor->next;
    pos_cursor += 1;
    return beforeCursor->data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over.
// Pre: position()>0
ListElement List::movePrev(){
    if (pos_cursor < 0){
        throw range_error("List: movePrev(): cursor out of range.");
    }
    beforeCursor = beforeCursor->prev;
    afterCursor = afterCursor->prev;
    pos_cursor -= 1;
    return afterCursor->data;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x){
    if (pos_cursor < 0){
        throw range_error("List: insertAfter(): cursor out of range.");
    }
    if (beforeCursor==nullptr || afterCursor==nullptr){
        throw range_error("List: insertAfter(): cursor are NULL.");
    }
    Node *N = new Node(x);
    N->prev = beforeCursor;
    beforeCursor->next = N;
    N->next = afterCursor;
    afterCursor->prev = N;
    afterCursor = N;
    num_elements += 1;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){
    if (pos_cursor < 0){
        throw range_error("List: insertBefore(): cursor out of range.");
    }
    if (beforeCursor==nullptr || afterCursor==nullptr){
        throw range_error("List: insertBefore(): cursor are NULL.");
    }
    Node *N = new Node(x);
    N->prev = beforeCursor;
    beforeCursor->next = N;
    N->next = afterCursor;
    afterCursor->prev = N;
    beforeCursor = N;
    num_elements += 1;
    pos_cursor += 1;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// Pre: position()<length()
void List::setAfter(ListElement x){
    if (pos_cursor >= length()){
        throw range_error("List: setAfter(): cursor out of range.");
    }
    afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// Pre: position()>0
void List::setBefore(ListElement x){
    if (pos_cursor <= 0){
        throw range_error("List: setBefore(): cursor out of range.");
    }
    beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// Pre: position()<length()
void List::eraseAfter(){
    if (pos_cursor >= length()){
        throw range_error("List: eraseAfter(): cursor out of range.");
    }
    Node *N = afterCursor;
    beforeCursor->next = afterCursor->next;
    N->next->prev = beforeCursor;
    afterCursor = N->next;
    delete N;
    num_elements -= 1;
}

// eraseBefore()
// Deletes element before cursor.
// Pre: position()>0
void List::eraseBefore(){
    if (pos_cursor <= 0){
        throw range_error("List: eraseBefore(): cursor out of range.");
    }
    Node *N = beforeCursor;
    afterCursor->prev = beforeCursor->prev;
    N->prev->next = afterCursor;
    beforeCursor = N->prev;
    delete N;
    num_elements -= 1;
    pos_cursor -= 1;
}


// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position length(), and returns -1.
int List::findNext(ListElement x){
    Node *N = afterCursor;
    for (int i=pos_cursor; N!=backDummy; i++){
        if ((N->data) == x){
            afterCursor = N->next;
            beforeCursor = N;
            pos_cursor = i + 1;
            return pos_cursor;
        }
        N = N->next;
    }
    afterCursor = backDummy;
    beforeCursor = backDummy->prev;
    pos_cursor = num_elements;
    return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position 0, and returns -1.
int List::findPrev(ListElement x){
    Node* temp = afterCursor->prev;
    int prevPos = pos_cursor - 1;
    while (temp != frontDummy) {
        if (temp->data == x) {
            beforeCursor = temp->prev;
            afterCursor = temp;
            pos_cursor = prevPos;
            return prevPos;
        }
        temp = temp->prev;
        prevPos -= 1;
    }
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
    return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost
// occurrance of each element, and removing all other occurances. The cursor
// is not moved with respect to the retained elements, i.e. it lies between
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){
   int pos = 0;
   Node *cursor = frontDummy->next;
   do {
      Node *current = cursor;
      Node *n = cursor->next;
      int inner_pos = pos + 1;
      while (n != backDummy) {
         if (cursor->data == n->data) {
               current->next = n->next;
               n->next->prev = current;
               delete n;
               n = current->next;
               num_elements -= 1;
               if (inner_pos <= pos_cursor) {
                  pos_cursor -= 1;
               }
         }
         else {
               current = n;
               n = current->next;
         }
         inner_pos += 1;
      }
      pos += 1;
      cursor = cursor->next;
   } while (cursor != backDummy);

}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{
    List M = List();
    for (Node *N1 = frontDummy->next; N1!=backDummy; N1=N1->next){
        M.insertBefore(N1->data);
    }
    for (Node *N2 = L.frontDummy->next; N2!=L.backDummy; N2=N2->next){
        M.insertBefore(N2->data);
    }
    M.moveFront();
    return M;
}

// to_string()
// Returns a string representation of this List consisting of a comma
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
    Node *N = frontDummy->next;
    std::string s = "(";
    while (N != backDummy){
        s += std::to_string(N->data);
        if ((N->next) != backDummy){
            s += ", ";
        }
        N = N->next;
    }
    s += ")";
    return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
    if (length() != R.length()){
        return false;
    }
    Node *N = frontDummy->next;
    Node *M = R.frontDummy->next;
    for (; N!=backDummy; N=N->next, M=M->next){
        if ((N->data) != (M->data)){
            return false;
        }
    }
    return true;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ){
    return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
    return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
    if (this != &L){
        List temp = L;
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(pos_cursor, temp.pos_cursor);
        std::swap(num_elements, temp.num_elements);
    }
    return *this;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             