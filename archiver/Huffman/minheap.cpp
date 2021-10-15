#include "minheap.h"

void MinHeap::push(Node *x) {
    v.push_back(x);
    size_t i = v.size() - 1;
    while (i > 0 && v[i]->sum < v[(i - 1) / 2]->sum) {
        std::swap(v[i], v[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void MinHeap::pop() {
    std::swap(v[0], v[v.size() - 1]);
    v.pop_back();
    heapify(0);
}

Node *MinHeap::top() {
    return v[0];
}
void MinHeap::heapify(size_t i) {
    size_t best = i;
    if (2 * i + 1 < v.size() && v[best]->sum > v[2 * i + 1]->sum) {
        best = 2 * i + 1;
    }
    if (2 * i + 2 < v.size() && v[best]->sum > v[2 * i + 2]->sum) {
        best = 2 * i + 2;
    }
    if (i == best) {
        return;
    }
    std::swap(v[i], v[best]);
    heapify(best);
}
size_t MinHeap::size() {
    return v.size();
}
