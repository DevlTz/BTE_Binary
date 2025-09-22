#pragma once

#include <string>
#include <vector>
#include <memory>

struct Node {
    bool is_op;
    char op; // valid if is_op == true
    long long val; // valid is_op == false
    Node* left;
    Node* right;
    Node(long long v): is_op(false), op('\0'), val(v), left(nullptr), right(nullptr) {}
    Node(char o, Node* l, Node* r): is_op(true), op(o), val(0), left(l), right(r) {}
};

Node* parse_rpn_expression(const std::vector<std::string>& tokens);
long long evaluate_tree(const Node* root);
void free_tree(Node* root);
std::string pretty_print(const Node* root);

