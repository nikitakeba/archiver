#include "node.h"

std::unique_ptr<Node> CreateParentNode(std::unique_ptr<Node> node1, std::unique_ptr<Node> node2) {
    std::unique_ptr<Node> n = std::make_unique<Node>();
    n->left = std::move(node1);
    n->right = std::move(node2);
    n->sum = n->left->sum + n->right->sum;
    return n;
}

std::unique_ptr<Node> NewLeaveNode(int freq, uint16_t symbol) {
    std::unique_ptr<Node> n = std::make_unique<Node>();
    n->sum = freq;
    n->c = symbol;
    n->is_leave = true;
    return n;
}
Node::Node() : left(nullptr), right(nullptr), is_leave(false), sum(0), c(0) {
}
