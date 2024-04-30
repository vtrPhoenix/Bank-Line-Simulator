/* 
 * BinaryHeap.cpp
 *
 * Description: Min Binary Heap ADT class.
 *
 * Class Invariant:  Always a Min Binary Heap.
 * 
 * Author: Vansh Thakur Rana (vtr)
 *         Agrim Joshi (aja121)
 * Last Modification: Apr. 2024
 *
 */  

#include <iostream>
#include "BinaryHeap.h"  // Header file
#include <cmath>

using std::cout;
using std::endl;

// Description: Constructor
template <class ElementType>
BinaryHeap<ElementType>::BinaryHeap() {
   elements = new ElementType[INITIAL_CAPACITY];
   elementCount = 0;
}

// Description: Destructor
template <class ElementType>
BinaryHeap<ElementType>::~BinaryHeap() {
   delete[] elements;
}

// Description: Copy Constructor
template <class ElementType>
BinaryHeap<ElementType>::BinaryHeap(const ElementType &newElement) {
   capacity = newElement.capacity; //copy capacity
   elementCount = newElement.elementCount; //copy element count

   elements = new ElementType[capacity]; //allocate memory for elements array
   for (unsigned int i = 0; i < capacity; i++) {
      elements[i] = newElement[i]; //copy elements
   }
}

// Description: Overloaded Assignment Operator
template <class ElementType>
ElementType& BinaryHeap<ElementType>::operator=(const ElementType &newElement) {
   if (this != &newElement) {
      delete[] elements; //Deallocate existing memory

      elements(newElement);
   }
   return *this;
}

// Description: Returns the number of elements in the Binary Heap.
// Postcondition: The Binary Heap is unchanged by this operation.
// Time Efficiency: O(1)
template <class ElementType>
unsigned int BinaryHeap<ElementType>::getElementCount() const {
   return elementCount;
}

// Description: Inserts newElement into the Binary Heap.
//              It returns true if successful, otherwise false.
// Time Efficiency: O(log2 n)
template <class ElementType>
bool BinaryHeap<ElementType>::insert(ElementType &newElement) {
   if (elementCount == capacity) { //If array is full resize it
      resize(capacity*2);
   }

   //unsigned int indexOfRoot = 0;
   unsigned int indexOfBottom = elementCount; //Index of new element

   elements[indexOfBottom] = newElement; //Insert new element
   elementCount++; //Increment element count

   if (elementCount > 1)
      reHeapUp(indexOfBottom); //Restore heap order

   return true; 
}

// Description: Recursively put the array back into a Min Binary Heap.
template <class ElementType>
void BinaryHeap<ElementType>::reHeapUp(unsigned int indexOfBottom) {

   if (indexOfBottom > 0) {
      unsigned int indexOfParent = floor((indexOfBottom-1)/2); //Calculate parent Index

      if (elements[indexOfBottom] <= elements[indexOfParent]) {
         // Swap the parent and the current element
         ElementType temp = elements[indexOfBottom];
         elements[indexOfBottom] = elements[indexOfParent];
         elements[indexOfParent] = temp;

         // Recursively put array back in heap
         reHeapUp(indexOfParent);
      }
   }
   return;
}


// Description: Retrieves (but does not remove) the necessary element.
// Precondition: This Binary Heap is not empty.
// Postcondition: This Binary Heap is unchanged.
// Exceptions: Throws EmptyDataCollectionException if this Binary Heap is empty.
// Time Efficiency: O(1)
template <class ElementType>
ElementType & BinaryHeap<ElementType>::retrieve() const {
   if (elementCount == 0)
      throw EmptyDataCollectionException("retrieve() callec with an empty BinaryHeap");

   return elements[0]; // Return root elements
}

// Description: Removes (but does not return) the necessary element.
// Precondition: This Binary Heap is not empty.
// Exceptions: Throws EmptyDataCollectionException if this Binary Heap is empty.
// Time Efficiency: O(log2 n)
template <class ElementType>
void BinaryHeap<ElementType>::remove() {  

   if(elementCount == 0) 
      throw EmptyDataCollectionException("remove() called with an empty BinaryHeap.");

   elements[0] = elements[elementCount - 1]; //Replace root with last element
   elementCount--; //decrement element count
   
   // No need to call reheapDown() is we have just removed the only element
   if ( elementCount > 0 ) 
      reHeapDown(0); //Restore heap order

   if (elementCount < (capacity/4) && ((capacity/2) >= INITIAL_CAPACITY)) {
      resize(capacity/2); //Shrink array if necessary
   } 
   
   return;   
}

// Utility method
// Description: Recursively put the array back into a Min Binary Heap.
template <class ElementType>
void BinaryHeap<ElementType>::reHeapDown(unsigned int indexOfRoot) {

   unsigned int indexOfMinChild = indexOfRoot;
   
   // Find indices of children.
   unsigned int indexOfLeftChild = 2 * indexOfRoot + 1;
   unsigned int indexOfRightChild = 2 * indexOfRoot + 2;

   // Base case: elements[indexOfRoot] is a leaf as it has no children
   if (indexOfLeftChild > elementCount - 1) return;

   // If we need to swap, select the smallest child
   // If (elements[indexOfRoot] > elements[indexOfLeftChild])
   if ( ! (elements[indexOfRoot] <= elements[indexOfLeftChild]) )
      indexOfMinChild = indexOfLeftChild;

   // Check if there is a right child, is it the smallest?
   if (indexOfRightChild < elementCount) {
      // if (elements[indexOfMinChild] > elements[indexOfRightChild])
      if ( ! (elements[indexOfMinChild] <= elements[indexOfRightChild]) )
         indexOfMinChild = indexOfRightChild;
   }

   // Swap parent with smallest of children.
   if (indexOfMinChild != indexOfRoot) {
      
      ElementType temp = elements[indexOfRoot];
      elements[indexOfRoot] = elements[indexOfMinChild];
      elements[indexOfMinChild] = temp;
      
      // Recursively put the array back into a heap
      reHeapDown(indexOfMinChild);
   }
   return;
} 


// Description: Resize the array
template <class ElementType>
void BinaryHeap<ElementType>::resize(unsigned int newCapacity) {
   ElementType * newElements = new ElementType[newCapacity];
   for (unsigned int i = 0; i < elementCount; i++) {
      newElements[i] = elements[i];
   }

   delete[] elements;
   elements = newElements;
   capacity = newCapacity;
}


// For testing purposes
template <class ElementType>
void BinaryHeap<ElementType>::print() {
   if (elementCount == 0)
      throw EmptyDataCollectionException("print() was called with an empty Heap.");

   for (unsigned int i = 0; i < elementCount; i++) {
      ElementType temp = elements[i];
      cout << temp << " ";
   }
   return;
}