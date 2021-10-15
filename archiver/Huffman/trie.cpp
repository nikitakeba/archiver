#include "trie.h"

void Traverse(Node* node, size_t len, std::map<uint16_t, size_t> &ans) {
    if (node->is_leave) {
        ans[node->c] = len;
        return;
    }
    if (node->left) {
        Traverse(node->left, len + 1, ans);
    }
    if (node->right) {
        Traverse(node->right, len + 1, ans);
    }
}

std::map<uint16_t, size_t> GetCodes(Node* root) {
    std::map<uint16_t, size_t> ans;
    Traverse(root, 0, ans);
    return ans;
}
