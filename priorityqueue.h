/*
Muhammad Muzzammil
UIN: 661-657-007
System used: Replit
Program 4
CS 251
*/
#pragma once

#include <iostream>
#include <set>
#include <sstream>

using namespace std;

template <typename T> class priorityqueue {
private:
  struct NODE {
    int priority; // used to build BST
    T value;      // stored data for the p-queue
    bool dup;     // marked true when there are duplicate priorities
    NODE *parent; // links back to parent
    NODE *link;   // links to linked list of NODES with duplicate priorities
    NODE *left;   // links to left child
    NODE *right;  // links to right child
  };
  NODE *root; // pointer to root node of the BST
  int size;   // # of elements in the pqueue
  NODE *curr; // pointer to next item in pqueue (see begin and next)

public:
  //
  // default constructor:
  //
  // Creates an empty priority queue.
  // O(1)
  //
  priorityqueue() {
    size = 0;
    root = nullptr;
    curr = nullptr;
  }

  //
  // operator=
  //
  // Clears "this" tree and then makes a copy of the "other" tree.
  // Sets all member variables appropriately.
  // O(n), where n is total number of nodes in custom BST
  //
  priorityqueue &operator=(const priorityqueue &other) {

    // TO DO: write this function.
    return *this;
  }

  //
  // clear:
  //
  // Frees the memory associated with the priority queue but is public.
  // O(n), where n is total number of nodes in custom BST
  //
  void clear() {

    
    // TO DO: write this function.
  }

  //
  // destructor:
  //
  // Frees the memory associated with the priority queue.
  // O(n), where n is total number of nodes in custom BST
  //
  ~priorityqueue() {

    // TO DO: write this function.
  }

  // my recursive function for enqueue
  void addNode(NODE *newNode, NODE *current) {
    if (newNode->priority == current->priority) {
      NODE *cursor = current;
      while (cursor->link != nullptr) {
        cursor = cursor->link;
      }
      cursor->link = newNode;

    } else if (newNode->priority > current->priority) {
      if (current->right != nullptr) {
        return addNode(newNode, current->right);
      }
      current->right = newNode;
    } else {
      if (current->left != nullptr) {
        return addNode(newNode, current->left);
      }
      current->left = newNode;
    }
  }

  //
  // enqueue:
  //
  // Inserts the value into the custom BST in the correct location based on
  // priority.
  // O(logn + m), where n is number of unique nodes in tree and m is number of
  // duplicate priorities
  //
  void enqueue(T value, int priority) {
    NODE *myNode = new NODE();
    myNode->value = value;
    myNode->priority = priority;

    if (root == nullptr) {
      root = myNode;
    } else {
      addNode(myNode, root);
    }
    size++;
  }

  T topRec(NODE *curr) {
    if (curr->left != nullptr) {
      return topRec(curr->left);
    }
    return curr->value;
  }

  T peek() {
    if (root != nullptr) {
      return topRec(root);
    }
    return nullptr;
  }

  NODE *dequeueRec(NODE *current) {
    if (current->left != nullptr) {
      NODE *newNode = dequeueRec(current->left);
      current->left = newNode;
      return current;
    } else if (current->link != nullptr) {
      current->link->right = current->right;
      // deconstruct current
      return current->link;
    }
    // deconstruct current
    return current->right;
  }

  //
  // dequeue:
  //
  // returns the value of the next element in the priority queue and removes
  // the element from the priority queue.
  // O(logn + m), where n is number of unique nodes in tree and m is number of
  // duplicate priorities
  //
  T dequeue() {
    T value = peek();
    if (root != nullptr) {
      root = dequeueRec(root);
      return value;
    }
    return value;
  }

  //
  // Size:
  //
  // Returns the # of elements in the priority queue, 0 if empty.
  // O(1)
  //
  int Size() { return size; }

  //
  // begin
  //
  // Resets internal state for an inorder traversal.  After the
  // call to begin(), the internal state denotes the first inorder
  // node; this ensure that first call to next() function returns
  // the first inorder node value.
  //
  // O(logn), where n is number of unique nodes in tree
  //
  // Example usage:
  //    pq.begin();
  //    while (tree.next(value, priority)) {
  //      cout << priority << " value: " << value << endl;
  //    }
  //    cout << priority << " value: " << value << endl;
  void begin() {

    // TO DO: write this function.
  }



  NODE *rec(NODE *curr){

    NODE *startNode = root;
    while(startNode->parent != nullptr){
      if(startNode->priority < startNode->parent->priority){
        startNode = startNode->parent;
        return startNode;
      }
      else{
        startNode = startNode->parent;
      }
    }
    return nullptr;
  }

  //
  // next
  //
  // Uses the internal state to return the next inorder priority, and
  // then advances the internal state in anticipation of future
  // calls.  If a value/priority are in fact returned (via the reference
  // parameter), true is also returned.
  //
  // False is returned when the internal state has reached null,
  // meaning no more values/priorities are available.  This is the end of the
  // inorder traversal.
  //
  // O(logn), where n is the number of unique nodes in tree
  //
  // Example usage:
  //    pq.begin();
  //    while (pq.next(value, priority)) {
  //      cout << priority << " value: " << value << endl;
  //    }
  //    cout << priority << " value: " << value << endl;
  //
  bool next(T &value, int &priority) {

    NODE *temp1 = NULL;
    NODE *temp2 = NULL;

    while(curr != nullptr){
      value = curr->value;
      priority = curr->priority;

      if(curr->link != NULL){
        temp1 = curr->right;
        temp2 = curr->parent;
        curr = curr->link;
        curr->right = temp1;
        curr->parent = temp2;
        return true;
      }
        
      else if(curr->right != NULL){
        curr = curr->right;
        curr = dequeueRec(curr);
        return true;
      }
      else{
        curr = rec(curr);
        return true;
      }
    }

    return false;
  }

  // my recursive function for toString
  void listInOrder(NODE *curr, ostream &stream) {

    if (curr->left != nullptr) {
      listInOrder(curr->left, stream);
    }

    NODE *cursor = curr;
    while (cursor != nullptr) {
      stream << cursor->priority << " value: " << cursor->value << endl;
      cursor = cursor->link;
    }

    if (curr->right != nullptr) {
      listInOrder(curr->right, stream);
    }
    return;
  }

  //
  // toString:

  // Returns a string of the entire priority queue, in order.  Format:
  // "1 value: Ben
  //  2 value: Jen
  //  2 value: Sven
  //  3 value: Gwen"
  //
  string toString() {
    if (root != nullptr) {
      listInOrder(root, cout);
    }
    return "";
  }

  //
  // ==operator
  //
  // Returns true if this priority queue as the priority queue passed in as
  // other.  Otherwise returns false.
  // O(n), where n is total number of nodes in custom BST
  //
  bool operator==(const priorityqueue &other) const {

    // TO DO: write this function.
    return true; // TO DO: update this return
  }

  //
  // getRoot - Do not edit/change!
  //
  // Used for testing the BST.
  // return the root node for testing.
  //
  NODE *getRoot() { return root; }
};
