#ifndef LISTNODE_H
#define LISTNODE_H
struct ListNode {
    std::string data;
    int priority;
    ListNode* next;
    ListNode() : data(""), priority(0), next(nullptr){}
    ListNode(std::string data_, int priority_): data(data_), priority(priority_), next(nullptr)  {}
};

#endif // LISTNODE_H