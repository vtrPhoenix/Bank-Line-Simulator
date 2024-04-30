/*
 * PriorityQueue.h
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

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "Event.h"
#include "BinaryHeap.h"
#include "EmptyDataCollectionException.h"


template <class ElementType>
class PriorityQueue {

    private:
        BinaryHeap<ElementType> queueP;
        unsigned int elementCount = 0;

    public:
        // Description: Constructor
        PriorityQueue();

        // Description: Returns the number of elements in the Priority Queue
        // Postcondition: The Priority Queue is unchanged by this operation.
        // Time Efficiency: O(1)
        unsigned int getElementCount() const;

        // Description: Returns true if this Priority Queue is empty, otherwise false.
        // Postcondition: This Priority Queue is unchanged by this operation.
        // Time Efficiency: O(1)
        bool isEmpty() const;

        // Description: Inserts newElement in this Priority Queue and
        //              returns true if successful, otherwise false.
        // Time Efficiency: O(log2 n)
        bool enqueue(ElementType &newElement);

        // Description: Removes (but does not return) the element with the next
        //              "highest" priority value from the Priority Queue.
        // Precondition: This Priority Queue is not empty.
        // Exception: Throws EmptyDataCollectionException if Priority Queue is empty.
        // Time Efficiency: O(log2 n)
        void dequeue();

        // Description: Returns (but does not remove) the element with the next
        //              "highest" priority value from the Priority Queue.
        // Precondition: This Priority Queue is not empty.
        // Postcondition: This Priority Queue is unchanged by this operation.
        // Exception: Throws EmptyDataCollectionException if this Priority Queue is empty.
        // Time Efficiency: O(1)
        ElementType &peek() const;
};
#include "PriorityQueue.cpp"
#endif