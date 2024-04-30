/*
 * BankSimApp.cpp
 * 
 * Class Description: Simulates a line up with one teller.
 *					  Calculates the average wait time for each customer.
 *					  Also outputs the number of customers and the time of each
 *					  customer's arrival/departure in order.
 *
 * Author: Vansh Thakur Rana (vtr) & Agrim Joshi (aja121)
 * Last Modification: Apr. 2024
 */

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "Event.h"
#include "Queue.h"
#include "PriorityQueue.h"
#include "BinaryHeap.h"

#include "EmptyDataCollectionException.h"

using namespace std;

int sum = 0;   // To store the sum of wait time

// Processes an arrival event
void processArrival (Event& arrivalEvent, PriorityQueue<Event>& eventPriorityQueue, Queue<Event>& bankLine, int& currentTime, bool& tellerAvailable) {
    cout << "Processing an arrival event at time:" << setw(6) << right << currentTime << endl;
    // Remove this event from the event queue
    eventPriorityQueue.dequeue();
    int departureTime;
    if (bankLine.isEmpty() && tellerAvailable) {
        departureTime = currentTime + arrivalEvent.getLength();
        Event departureEvent = Event('D', departureTime);
        eventPriorityQueue.enqueue(departureEvent);
        tellerAvailable = false;
    }
    else {
        bankLine.enqueue(arrivalEvent);
    }
}

// Processes a departure event
void processDeparture (Event& departureEvent, PriorityQueue<Event>& eventPriorityQueue, Queue<Event>& bankLine, int& currentTime, bool& tellerAvailable) {
    cout << "Processing a departure event at time:" << setw(5) << right << currentTime << endl;
    // Remove this event from the event queue
    eventPriorityQueue.dequeue();

    int departureTime;

    if (!bankLine.isEmpty()){

        try {
            // Customer at front of line begins transaction
            Event customer = bankLine.peek();
            sum = sum + currentTime - customer.getTime();
            bankLine.dequeue();
            departureTime = currentTime + customer.getLength();
            Event newDepartureEvent = Event('D', departureTime);
            eventPriorityQueue.enqueue(newDepartureEvent);
        } catch (EmptyDataCollectionException& exception) {
            cout << exception.what() << endl;
        }

    } else
        tellerAvailable = true;
}


int main() {
    // Simulation Begins
    cout << "Simulation Begins" << endl;

    int currentTime = 0;
    Queue<Event> bankLine = Queue<Event>();           // Bank Line
    PriorityQueue<Event> eventPriorityQueue = PriorityQueue<Event>();   // Event Queue

    bool tellerAvailable = true;
    int customerCount = 0;        // Number of customers
    
    string aLine = "";
    int length = 0;
    int time = 0;
    Event newArrivalEvent;             // Arrival Event

    // Add arrival events to the event queue
    while (getline(cin >> ws, aLine)) {
        stringstream ss (aLine);                     // Read from the input file
        ss >> time >> length;
        newArrivalEvent.setLength(length);           // Set length of transaction time for a customer
        newArrivalEvent.setTime(time);               // Set required transaction time for a customer

        if (!eventPriorityQueue.enqueue(newArrivalEvent)) {
            return 1;
        }
    }
    customerCount = eventPriorityQueue.getElementCount();       // Set customer count from input file

    // Event Loop
    while (!eventPriorityQueue.isEmpty()) {
        try {
            Event newEvent = eventPriorityQueue.peek();
            // Get current time
            currentTime = newEvent.getTime();

            if (newEvent.getType() == Event::ARRIVAL) {
                // Call the Arrival process function
                processArrival(newEvent, eventPriorityQueue, bankLine, currentTime, tellerAvailable);
            }
            else {
                // Call the Departure process function
                processDeparture(newEvent, eventPriorityQueue, bankLine, currentTime, tellerAvailable);
            }
        }
        catch (EmptyDataCollectionException & anException) {
            cout << anException.what() << endl;
        }
    }

    cout << "Simulation Ends" << endl;
    cout << endl;
    cout << "Final Statistics: " << endl;
    cout << endl;
    cout << "    Total number of people processed: " << customerCount << endl;
    cout << "    Average amount of time spent waiting: " << float(sum)/float(customerCount) << endl;

    return 0;
}