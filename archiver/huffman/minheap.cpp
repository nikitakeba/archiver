#include "minheap.h"

void MinHeap::push(std::unique_ptr<Node> x) {
    v.push_back(std::move(x));
    size_t i = v.size() - 1;
    while (i > 0 && v[i]->sum < v[(i - 1) / 2]->sum) {
        std::swap(v[i], v[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

std::unique_ptr<Node> MinHeap::pop() {
    auto tmp = std::unique_ptr<Node>(v[0].release());
    std::swap(v[0], v[v.size() - 1]);
    v.pop_back();
    heapify(0);
    return tmp;
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
size_t MinHeap::size() const {
    return v.size();
}
