#ifndef USLINKEDPRIORITYQUEUE_H
#define USLINKEDPRIORITYQUEUE_H

#include <string>
#include <iostream>
#include <limits>
#include "error.h"
#include "listnode.h"

/*struct ListNode {
    std::string data;
    int priority;
    ListNode* next;
    ListNode() : data(""), priority(0), next(nullptr){}
    ListNode(std::string data_, int priority_): data(data_), priority(priority_), next(nullptr)  {}
};
*/
class USLinkedPriorityQueue
{
public:
    USLinkedPriorityQueue() {front = NULL;}
    ~USLinkedPriorityQueue() {clear();}
    void enqueue(std::string data_, int priority_);
    void dequeue();
    std::string peek();
    int peekPriority();
    void changePriority(std::string data_, int newPriority_);
    bool isEmpty();
    int size();
    void clear();
    friend std::ostream& operator<<(std::ostream& out, USLinkedPriorityQueue& pq);
private:
     ListNode* front;
     ListNode* getUrgent();
};

#endif // USLINKEDPRIORITYQUEUE_H
