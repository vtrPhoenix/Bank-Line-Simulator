/*
 * PriorityQueue.cpp
 *
 * Description: Models a Priority Queue
 *
 * Class Invariant: FIFO or LILO order using priority value
 *                  Sorted by time and type
 *
 * Author: Vansh Thakur Rana (vtr)
 *         Agrim Joshi (aja121)
 * Last Modified: Apr. 2024
 */

#include <iostream>
#include "PriorityQueue.h"

using std::cout;
using std::endl;

// Description: Constructor
template <class ElementType>
PriorityQueue<ElementType>::PriorityQueue() {
    elementCount = 0;
}


// Description: Returns the number of elements in the Priority Queue.
// Postcondition: The Priority Queue is unchanged by this operation.
// Time Efficiency: O(1)
template <class ElementType>
unsigned int PriorityQueue<ElementType>::getElementCount() const {
    return elementCount;
}

// Description: Returns true if this Priority Queue is empty, otherwise false.
// Postcondition: This Priority Queue is unchanged by this operation.
// Time Efficiency: O(1)
template <class ElementType>
bool PriorityQueue<ElementType>::isEmpty() const {
    if (queueP.getElementCount() == 0)
        return true;
    return false;
}

// Description: Inserts newElement in this Priority Queue and
//              returns true if successful, otherwise false.
// Time Efficiency: O(log2 n)
template <class ElementType>
bool PriorityQueue<ElementType>::enqueue(ElementType &newElement) {
    queueP.insert(newElement);
    elementCount++;

    return true;
}

// Description: Removes (but does not return) the element with the next
//              "highest" priority value from the Priority Queue.
// Precondition: This Priority Queue is not empty.
// Exception: Throws EmptyDataCollectionException if Priority Queue is empty.
// Time Efficiency: O(log2 n)
template <class ElementType>
void PriorityQueue<ElementType>::dequeue() {
    if(isEmpty())
        throw EmptyDataCollectionException("dequeue() called on an empty Priority Queue.");
    queueP.remove();
    elementCount--;
}

// Description: Returns (but does not remove) the element with the next
//              "highest" priority value from the Priority Queue.
// Precondition: This Priority Queue is not empty.
// Postcondition: This Priority Queue is unchanged by this operation.
// Exception: Throws EmptyDataCollectionException if this Priority Queue is empty.
// Time Efficiency: O(1)
template <class ElementType>
ElementType & PriorityQueue<ElementType>::peek() const {
    if(isEmpty())
        throw EmptyDataCollectionException("peek() called on an empty Priority Queue.");
    return queueP.retrieve();
}