#include "uslinkedpriorityqueue.h"

// O(1)
void USLinkedPriorityQueue::enqueue(std::string data_, int priority_) {
    if (isEmpty()) {
        front = new ListNode(data_, priority_);
    } else {
        ListNode* newFront = new ListNode(data_, priority_);
        newFront->next = front;
        front = newFront;
    }
}

// O(N)
void USLinkedPriorityQueue::dequeue() {
    if (isEmpty()) {
        error("nothing to dequeue");
    } else {
        ListNode* urgent = getUrgent();
        ListNode* curr = front;
        ListNode* prev = front;
        while (curr) {
            if (urgent == curr) {
                prev->next = curr->next;
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }
}
// O(N)
std::string USLinkedPriorityQueue::peek() {
    if (isEmpty()) {
        error ("nothing inside");
    }
    ListNode* urgent = getUrgent();
    return urgent->data;

}
// O(N)
int USLinkedPriorityQueue::peekPriority() {
    if (isEmpty()) {
        error ("nothing inside");
    }
    ListNode* urgent = getUrgent();
    return urgent->priority;
}
// O(N)
void USLinkedPriorityQueue::changePriority(std::string data_, int newPriority_) {
    if (isEmpty()) {
        error("nothing inside");
    } else {
        ListNode* curr = front;
        while (curr) {
            if (curr->data == data_) {
                if (curr->priority > newPriority_) {
                    curr->priority = newPriority_;
                    return;
                } else {
                    error("not Urgent LA");
                }
            }
        }
        error ("bro no such value");
    }
}

bool USLinkedPriorityQueue::isEmpty() {
    return (front == NULL);
}

int USLinkedPriorityQueue::size() {
    int count = 0;
    ListNode* curr = front;
    while (curr) {
        curr = curr->next;
        count++;
    }
    return count;
}

void USLinkedPriorityQueue::clear() {
    if (isEmpty()) {
        std::cout << "nothing ler bro";
    }

    while (front) {
        ListNode *curr = front->next;
        delete front;
        front = curr;
    }
}

// O(N)
std::ostream& operator<<(std::ostream& out, USLinkedPriorityQueue& pq) {
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

// O(N)
ListNode* USLinkedPriorityQueue::getUrgent() {
    ListNode* curr = front;
    ListNode* urgent = new ListNode("", std::numeric_limits<int>::max()); // minimize probs
    while (curr) {
        if (urgent->priority > curr->priority) {
            urgent = curr;
        } else if (urgent->priority == curr->priority)
            if (urgent->data > curr->data) {
                urgent = curr;
            }
        curr = curr->next;
    }
    return urgent;
}
