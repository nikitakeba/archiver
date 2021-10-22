#include "huffman.h"

namespace {
void Add(Node* node, size_t pos, std::vector<bool>& code, uint16_t c) {
    if (pos == code.size()) {
        node->c = c;
        node->is_leave = true;
        return;
    }
    if (!code[pos]) {
        if (!node->left) {
            node->left = std::make_unique<Node>();
        }
        Add(node->left.get(), pos + 1, code, c);
    } else {
        if (!node->right) {
            node->right = std::make_unique<Node>();
        }
        Add(node->right.get(), pos + 1, code, c);
    }
}

std::unique_ptr<Node> Build(std::vector<uint16_t>& symbols, std::vector<int>& frequency) {
    MinHeap pq;

    for (size_t i = 0; i < symbols.size(); i++) {
        pq.push(NewLeaveNode(frequency[i], symbols[i]));
    }
    while (pq.size() > 1) {
        std::unique_ptr<Node> node1 = pq.pop();
        std::unique_ptr<Node> node2 = pq.pop();
        pq.push(CreateParentNode(std::move(node1), std::move(node2)));
    }

    return pq.pop();
}

std::map<uint16_t, size_t> GetLengths(std::vector<uint16_t>& symbols, std::vector<int>& frequency) {
    std::unique_ptr<Node> root = Build(symbols, frequency);
    std::map<uint16_t, size_t> mp = GetCodes(root.get());
    return mp;
}
}  // namespace

std::unique_ptr<Node> Huffman::BuildTrieByCodes(std::map<uint16_t, std::vector<bool>>& codes) {
    auto root = std::make_unique<Node>();
    for (auto& u : codes) {
        Add(root.get(), 0, u.second, u.first);
    }
    return root;
}

std::map<uint16_t, std::vector<bool>> Huffman::GetCanonicalCodes(std::map<uint16_t, size_t>& mp) {
    std::vector<std::pair<size_t, uint16_t>> tmp;
    for (auto u : mp) {
        tmp.push_back(std::make_pair(u.second, u.first));
    }
    std::sort(tmp.begin(), tmp.end());
    std::vector<bool> cur;
    std::map<uint16_t, std::vector<bool>> codes;
    for (auto u : tmp) {

        while (cur.size() < u.first) {
            cur.push_back(0);
        }

        codes[u.second] = cur;

        size_t id;
        bool found = false;

        for (size_t i = 0; i < cur.size(); i++) {
            if (!cur[i]) {
                found = true;
                id = i;
            }
        }

        if (found) {
            for (size_t i = cur.size() - 1; i > id; i--) {
                cur[i] = 0;
            }
            cur[id] = true;
        } else {
            cur.push_back(false);
            cur[0] = true;
            for (size_t i = 1; i < cur.size(); i++) {
                cur[i] = false;
            }
        }
    }
    return codes;
}

std::map<uint16_t, std::vector<bool>> Huffman::GetCanonicalCodesBySymbols(std::vector<uint16_t>& symbols,
                                                                          std::vector<int>& frequency) {
    std::map<uint16_t, size_t> mp = GetLengths(symbols, frequency);
    std::map<uint16_t, std::vector<bool>> codes = GetCanonicalCodes(mp);
    return codes;
}
