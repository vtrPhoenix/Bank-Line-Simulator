/*
 * Queue.h
 *
 * Description: Models arrival and departure events.
 *
 * Class Invariant: FIFO or LILO order
 *
 * Author: Vansh Thakur Rana (vtr)
 *         Agrim Joshi (aja121)
 * Last Modified: Apr. 2024
 */

#ifndef QUEUE_H
#define QUEUE_H

#include"Event.h"
#include "EmptyDataCollectionException.h"

template <class ElementType>
class Queue {

    private:
        static unsigned int const INITIAL_CAPACITY = 6; // Constant INITIAL_CAPACITY
        ElementType *elements;

        unsigned int elementCount = 0;            // Number of elements in the Queue - if you need it!
        unsigned int capacity = INITIAL_CAPACITY; // Actual capacity of the data structure (number of cells in the array)
        unsigned int frontindex = 0;              // Index of front element (next dequeued/peeked element)
        unsigned int backindex = 0;               // Index of where the next element will be enqueued

        void resize(unsigned int newCapacity); // To resize the array

    public:

        // Description: Constructor
        Queue();

        // Description: Destructor
        ~Queue();

        // Description: Copy Constructor
        Queue(const ElementType &newElement);

        // Description: Overloaded Assignment operator
        ElementType & operator=(const ElementType &newElement);

        // Description: Constructor
        // Time Efficiency: O(1)
        bool isEmpty() const;

        // Description: Inserts newElement at the "back" of this Queue
        //              (not necessarily the "back" of this Queue's data structure)
        //              and returns true if successful, otherwise false.
        // Time Efficiency: O(1)
        bool enqueue(ElementType &newElement);

        // Description: Removes (but does not return) the element at the "front" of this Queue
        //              (not necessarily the "front" of this Queue's data structure).
        // Precondition: This Queue is not empty.
        // Exception: Throws EmptyDataCollectionException if this Queue is empty.
        // Time Efficiency: O(1)
        void dequeue();

        // Description: Returns (but does not remove) the element at the "front" of this Queue
        //              (not necessarily the "front" of this Queue's data structure).
        // Precondition: This Queue is not empty.
        // Postcondition: This Queue is unchanged by this operation.
        // Exception: Throws EmptyDataCollectionException if this Queue is empty.
        // Time Efficiency: O(1)
        ElementType &peek() const;
};
#include "Queue.cpp"
#endif
