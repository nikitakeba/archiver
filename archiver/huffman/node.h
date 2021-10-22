#ifndef NODE
#define NODE

#include <cstdint>
#include <memory>

struct Node {
    std::unique_ptr<Node> left = nullptr;
    std::unique_ptr<Node> right = nullptr;
    bool is_leave = false;
    int sum = 0;
    uint16_t c = 0;
    Node();
};

std::unique_ptr<Node> NewLeaveNode(int freq = 0, uint16_t symbol = 0);

std::unique_ptr<Node> CreateParentNode(std::unique_ptr<Node> node1, std::unique_ptr<Node> node2);

#endif
