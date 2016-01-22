#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "slinkedpriorityqueue.h"
#include "uslinkedpriorityqueue.h"
#include "heappriorityqueue.h"
using namespace std;

int main() {
    HeapPriorityQueue test1;
    cout << test1 << endl;
    test1.enqueue("a", 10);
    test1.changePriority("a",4);
    cout << test1 << endl;
    test1.enqueue("b",8);
    test1.enqueue("c", 6);
    test1.enqueue("d",7);
    test1.enqueue("k",9);
    test1.enqueue("e",4);
    test1.enqueue("z",9);

    test1.changePriority("z", 6);
       cout << test1 << endl;
    cout << test1.peek();
    cout << test1.peekPriority();
    test1.dequeue();

    test1.enqueue("e",200);
    cout << test1;
    cout << test1.size() << endl;
    test1.clear();
    cout << test1.size() << endl;
    cout << test1;
    test1.enqueue("r",9);
    test1.enqueue("d",9);
    test1.enqueue("a",9);
    test1.enqueue("v",9);
    cout << test1;
    test1.enqueue("t",1);


    cout << test1;

    return 0;
}
