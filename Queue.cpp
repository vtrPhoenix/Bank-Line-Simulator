/*
 * Queue.cpp
 *
 * Description: Models arrival and departure events.
 *
 * Class Invariant: FIFO or LILO order
 *
 * Author: Vansh Thakur Rana (vtr)
 *         Agrim Joshi (aja121)
 * Last Modified: Apr. 2024
 */

#include <iostream>
#include "Queue.h"

using std::cout;
using std::endl;

// Description: Constructor
template <class ElementType>
Queue<ElementType>::Queue()
{
    elements = new ElementType[INITIAL_CAPACITY]; // Create a dynamic array on the heap with INITIAL_CAPACITY
}

// Description: Destructor
template <class ElementType>
Queue<ElementType>::~Queue()
{
    delete[] elements;
}

// Description: Copy Constructor
template <class ElementType>
Queue<ElementType>::Queue(const ElementType &newElement)
{
    capacity = newElement.capacity;         // Set the capacity of new array
    elementCount = newElement.elementCount; // Set element count of new array
    frontindex = newElement.frontindex;     // Set front index of new array
    backindex = newElement.backindex;       // Set back index of new array

    elements = new ElementType[capacity];
    for (unsigned int i = 0; i < capacity; i++) // Copying elements from into the new array
    {
        elements[i] = newElement.elements[i];
    }
}

// Description: Overloaded Assignment Operator
template <class ElementType>
ElementType& Queue<ElementType>::operator=(const ElementType &newElement) {
    if (this != &newElement) {                     // Check if the array is not equal to the new array and delete the elements
        delete[] elements;

        capacity = newElement.capacity;                         // Set the capacity of new array
        elementCount = newElement.elementCount;                 // Set element count of new array
        frontindex = newElement.frontindex;                     // Set front index of new array
        backindex = newElement.backindex;                       // Set back index of new array

        elements = new ElementType[capacity];
        for (unsigned int i = 0; i < capacity; ++i) {           // Copying elements from into the new array
            elements[i] = newElement.elements[i];
        }
    }
    return *this;
}

// Description: Resize the array
template <class ElementType>
void Queue<ElementType>::resize(unsigned int newCapacity) {
    ElementType * newElements = new ElementType[newCapacity];               // Create new dynamic array using the new capacity set by enqueue or dequeue
    for (unsigned int i = 0; i < elementCount; i++) {            
        newElements[i] = elements[(frontindex + i) % capacity];            // Copying elements into the new array
    }

    delete[] elements;                // Clear the old array from the heap memory
    elements = newElements;
    frontindex = 0;
    backindex = elementCount;
    capacity = newCapacity;
}

// Description: Returns true if this Queue is empty, otherwise false.
// Postcondition: This Queue is unchanged by this operation.
// Time Efficiency: O(1)
template <class ElementType>
bool Queue<ElementType>::isEmpty() const {
    return elementCount == 0;
}

// Description: Inserts newElement at the "back" of this Queue
//              (not necessarily the "back" of this Queue's data structure)
//              and returns true if successful, otherwise false.
// Time Efficiency: O(1)
template <class ElementType>
bool Queue<ElementType>::enqueue(ElementType &newElement) {
    if (elementCount == capacity) {           // To check if the array needs to be resized to add the new element
        resize(capacity*2);
    }

    elementCount++;
    elements[backindex] = newElement;
    backindex = (backindex + 1) % capacity;    
    return true;
}

// Description: Removes (but does not return) the element at the "front" of this Queue
//              (not necessarily the "front" of this Queue's data structure).
// Precondition: This Queue is not empty.
// Exception: Throws EmptyDataCollectionException if this Queue is empty.
// Time Efficiency: O(1)
template <class ElementType>
void Queue<ElementType>::dequeue() {
    if (this->isEmpty())
        throw EmptyDataCollectionException("The Queue is empty.");
    
    elementCount--;
    frontindex = (frontindex + 1) % capacity;

    if(elementCount < (capacity/4) && ((capacity/2) >= INITIAL_CAPACITY)) {      // To check if the array needs to be shortened after removing the front element
        resize(capacity/2);
    }
    return;
}

// Description: Returns (but does not remove) the element at the "front" of this Queue
//              (not necessarily the "front" of this Queue's data structure).
// Precondition: This Queue is not empty.
// Postcondition: This Queue is unchanged by this operation.
// Exception: Throws EmptyDataCollectionException if this Queue is empty.
// Time Efficiency: O(1)
template <class ElementType>
ElementType &Queue<ElementType>::peek() const {
    if(this->isEmpty())
        throw EmptyDataCollectionException("The Queue is empty.");

    return elements[frontindex];
}
