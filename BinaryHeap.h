/*
 * BinaryHeap.h
 * 
 * Description: Min Binary Heap ADT class.
 *
 * Class Invariant:  Always a Min Binary Heap.
 * 
 * Author: Vansh Thakur Rana (vtr)
 *         Agrim Joshi (aja121)
 * Date of last modification: Apr. 2024
 */

#ifndef BinaryHeap_H
#define BinaryHeap_H

#include"Event.h"
#include "Queue.h"
#include "EmptyDataCollectionException.h"



template <class ElementType>
class BinaryHeap {

    private:

        ElementType *elements;

        static unsigned int const INITIAL_CAPACITY = 6; // Constant INITIAL_CAPACITY
        unsigned int elementCount = 0;            // Number of elements in the Binary Heap
        unsigned int capacity = INITIAL_CAPACITY; // Actual capacity of the data structure (number of cells in the array)

        // Utility method
        // Description: Recursively put the array back into a Min Binary Heap.
        void reHeapDown(unsigned int indexOfRoot);

        // Description: 
        void reHeapUp(unsigned int indexOfBottom);

        void resize(unsigned int newCapacity); // To resize the array

    public:

        // Description: Constructor
        BinaryHeap();

        // Description: Destructor
        ~BinaryHeap();

        // Description: Copy Constructor
        BinaryHeap(const ElementType &newElement);

        // Description: Overloaded Assignment Operator
        ElementType & operator=(const ElementType &newElement);

        // Description: Returns the number of elements in the Binary Heap.
        // Postcondition: The Binary Heap is unchanged by this operation.
        // Time Efficiency: O(1)
        unsigned int getElementCount() const;

        // Description: Inserts newElement into the Binary Heap.
        //              It returns true if successful, otherwise false.
        // Time Efficiency: O(log2 n)
        bool insert(ElementType &newElement);

        // Description: Removes (but does not return) the necessary element.
        // Precondition: This Binary Heap is not empty.
        // Exceptions: Throws EmptyDataCollectionException if this Binary Heap is empty.
        // Time Efficiency: O(log2 n)
        void remove();

        // Description: Retrieves (but does not remove) the necessary element.
        // Precondition: This Binary Heap is not empty.
        // Postcondition: This Binary Heap is unchanged.
        // Exceptions: Throws EmptyDataCollectionException if this Binary Heap is empty.
        // Time Efficiency: O(1)
        ElementType &retrieve() const;


        // For testing purposes
        void print();
};
#include "BinaryHeap.cpp"
#endif