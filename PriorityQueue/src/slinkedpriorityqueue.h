#ifndef SLINKEDPRIORITYQUEUE_H
#define SLINKEDPRIORITYQUEUE_H

#include <string>
#include <iostream>
#include "error.h"
#include "listnode.h"

class SLinkedPriorityQueue
{
public:
    SLinkedPriorityQueue() {front = NULL;}
    ~SLinkedPriorityQueue() {clear();}
    void enqueue(std::string data_, int priority_);
    void dequeue();
    std::string peek();
    int peekPriority();
    void changePriority(std::string data_, int newPriority_);
    bool isEmpty();
    int size();
    void clear();
    friend std::ostream& operator<<(std::ostream& out, SLinkedPriorityQueue& pq);

private:
    ListNode* front;
    void deleteEntry();
};

#endif // SLINKEDPRIORITYQUEUE_H
