#ifndef HEAPPRIORITYQUEUE_H
#define HEAPPRIORITYQUEUE_H

#include <string>
#include <iostream>
#include <algorithm>
#include "error.h"

struct PQentry {
    std::string data;
    int priority;
    PQentry() : data(""), priority(0){}
    PQentry(std::string data_, int priority_): data(data_), priority(priority_) {}
};

class HeapPriorityQueue
{
public:
    HeapPriorityQueue() {capacity=10; mysize = 0;arr = new PQentry[capacity];}
    ~HeapPriorityQueue(){delete[] arr;}
    void enqueue(std::string data_, int priority_);
    void dequeue();
    std::string peek();
    int peekPriority();
    void changePriority(std::string data_, int newPriority_);
    bool isEmpty();
    int size();
    void clear();
    friend std::ostream& operator<<(std::ostream& out, const HeapPriorityQueue& pq);

private:
    PQentry * arr;
    int capacity;
    int mysize;
    void upheap(int index);
    void downheap(int i);
    void increaseSize();
    void downheapHelper(int child, int smallest);
};

#endif // HEAPPRIORITYQUEUE_H
