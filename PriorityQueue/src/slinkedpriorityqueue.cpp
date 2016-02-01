#include "slinkedpriorityqueue.h"


// O(n), where n is no. of nodes;
void SLinkedPriorityQueue::enqueue(std::string data_, int priority_) {
    if (isEmpty()) {
        front = new ListNode(data_,priority_);
    } else {
        ListNode * curr = front;
        while (curr->next && curr->next->priority <= priority_) {
            curr = curr->next;
            if (curr->priority == priority_ && data_ < curr->data) {
                std::string tempString = curr->data;
                curr->data = data_;
                data_ = tempString;
            }
        }
        ListNode *temp = new ListNode(data_, priority_);
        //do another loop to compare the string values
        if (priority_ < curr->priority) {
            temp->next = curr;
            front = temp;
        } else {
            temp->next = curr->next;
            curr->next = temp;
        }
    }
}


// O(1);
void SLinkedPriorityQueue::dequeue() {
    if (isEmpty()) {
        error("Empty Priority!");
    } else {
        deleteEntry();
    }
}

// O(1);
std::string SLinkedPriorityQueue::peek() {
    if (isEmpty()) {
        error("nothing!");
    }
    return front->data;
}

// O(1);
int SLinkedPriorityQueue::peekPriority() {
    if (isEmpty()) {
        error("nothing!");
    }
    return front->priority;
}

// O(N^2)
void SLinkedPriorityQueue::changePriority(std::string data_, int newPriority_) {
    if (isEmpty()) {
        error("kosongla");
    } else {
        ListNode* curr = front;
        ListNode* prev = front;
        while (curr) {
            if (curr-> data == data_) {
                if (curr->priority > newPriority_) {
                    prev->next = curr->next;
                    delete curr;
                    enqueue(data_, newPriority_);
                    return;
                } else {
                    error("Priority not urgent");
                }
            }
            prev = curr;
            curr = curr->next;
        }
        error ("cannot find value");
    }
}

bool SLinkedPriorityQueue::isEmpty() {
    return (front == NULL);
}

int SLinkedPriorityQueue::size() {
    int count = 0;
    ListNode* curr = front;
    while (curr) {
        curr = curr->next;
        count++;
    }
    return count;
}
//O(n)
void SLinkedPriorityQueue::clear() {
    if (isEmpty()) {
        std::cout << "nothing ler bro";
    }
    while (front) {
        deleteEntry();
    }
}

// O(N)
std::ostream& operator<<(std::ostream& out, SLinkedPriorityQueue& pq) {
    out << "{";
    ListNode* curr = pq.front;
    while (curr) {
        out << curr->data;
        out << ":";
        out << curr->priority;
        if (curr->next) {
            out << ", ";
        }
        curr = curr->next;
    }
    out << "}" ;
    return out;
}

// O(1)
void SLinkedPriorityQueue::deleteEntry() {
    ListNode* curr = front->next;
    delete front;
    front = curr;
}
