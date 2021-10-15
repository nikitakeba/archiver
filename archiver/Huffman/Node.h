#include <cstdint>
#pragma once

struct Node {
    Node* left = nullptr;
    Node* right = nullptr;
    bool is_leave = false;
    int sum = 0;
    uint16_t c;
    ~Node();
};


struct Comparator {
    bool operator()(Node* node1, Node* node2) {
        return node1->sum < node2->sum;
    }
};


Node* NewLeaveNode(int freq = 0, uint16_t symbol = 0);

Node* CreateParentNode(Node* node1, Node* node2);
