#ifndef MINHEAP
#define MINHEAP

#include <vector>
#include "node.h"

class MinHeap {
public:
    std::unique_ptr<Node> pop();
    void push(std::unique_ptr<Node> x);
    size_t size() const;

private:
    void heapify(size_t i);
    std::vector<std::unique_ptr<Node>> v;
};
#endif
