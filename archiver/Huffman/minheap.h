#include <vector>
#include "Node.h"

class MinHeap {
public:
    void pop();
    void push(Node* x);
    void heapify(size_t i);
    Node* top();
    size_t size();

    std::vector<Node*> v;
};
