#include "heappriorityqueue.h"

void HeapPriorityQueue::enqueue(std::string data_, int priority_) {
    mysize++;
    if (mysize > capacity) {
        increaseSize();
    }
    arr[mysize] = PQentry(data_, priority_);
    if (mysize > 1) {
        upheap(mysize-1);
    }
}

void HeapPriorityQueue::dequeue() {
    if (isEmpty()) {
        error("Nothing Inside");
    } else {
        downheap(1);
        mysize--;
    }
}

std::string HeapPriorityQueue::peek() {
    if (isEmpty()) {
        error("Nothing Inside");
    }
    return arr[1].data;
}

int HeapPriorityQueue::peekPriority() {
    if (isEmpty()) {
        error("Nothing Inside");
    }
    return arr[1].priority;
}

void HeapPriorityQueue::changePriority(std::string data_, int newPriority_) {
    if (isEmpty()) {
        error("nothing inside");
    }

    for (int i = 0 ; i <= mysize ; i++) {
        if (arr[i].data == data_) {
            if (arr[i].priority > newPriority_) {
                arr[i].priority = newPriority_;
                upheap(mysize - 1);
                return;
            } else {
                error("not so Urgent Brah!");
            }
        }
    }
    error("cant find val");
}

bool HeapPriorityQueue::isEmpty() {
    return (mysize == 0);
}

int HeapPriorityQueue::size() {
    return mysize;
}

void HeapPriorityQueue::clear() {
    mysize = 0;
}

std::ostream& operator<<(std::ostream& out, const HeapPriorityQueue& pq) {
    out << "{";
    for (int i = 1; i <= pq.mysize; i++) {
        out << pq.arr[i].data;
        out << ":";
        out << pq.arr[i].priority;
        if (i + 1 <= pq.mysize) {
            out << ",";
        }
    }
    out << "}";
    return out;
}

void HeapPriorityQueue::upheap(int index) {

    int parent = index / 2;

    while (index > 0 && arr[index].priority < arr[parent].priority) {
        std::swap(arr[index],arr[parent]);
        index = parent;
        parent /=2;
        index /= 2;
    }
}

void HeapPriorityQueue::downheap(int i) {
    int left = 2 * i;
    int right = (2 * i) + 1;
    int smallest = i;
    if (left <= mysize-1 && arr[left].priority <= arr[smallest].priority ) {
        downheapHelper(left, smallest);
        smallest = left;
    }

    if (right <= mysize-1 && arr[right].priority <= arr[smallest].priority) {
        downheapHelper(right, smallest);
        smallest = right;
    }

    if (smallest != i) {
        std::swap(arr[i], arr[smallest]);
        downheap(smallest);
    }
}

void HeapPriorityQueue::increaseSize() {
    capacity *=2;
    PQentry* temp = new PQentry[capacity];
    for (int i = 1; i <= mysize; i++) {
        temp[i] = arr[i];
    }
    delete[] arr;
    arr = temp;
}

void HeapPriorityQueue::downheapHelper(int child, int smallest) {
    if (arr[child].priority == arr[smallest].priority && arr[child].data < arr[smallest].data) {
        std::swap(arr[child].data, arr[smallest].data);
    }
}
