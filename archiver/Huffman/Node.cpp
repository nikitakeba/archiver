#include "Node.h"

Node* CreateParentNode(Node* node1, Node* node2) {
    Node* n = new Node();
    n->left = node1;
    n->right = node2;
    n->sum = node1->sum + node2->sum;
    return n;
}

Node* NewLeaveNode(int freq, uint16_t symbol) {
    Node* n = new Node();
    n->sum = freq;
    n->c = symbol;
    n->is_leave = true;
    return n;
}

Node::~Node() {
    if (this->left) {
        delete this->left;
    }
    if (this->right) {
        delete this->right;
    }
}
