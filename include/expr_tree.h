#pragma once

#include <string>
#include <vector>
#include <memory>

// Node (operator or value) using unique_ptr for children
struct Node {
    bool is_op;
    char op;                // valid if is_op
    long long val;          // valid if !is_op
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    // leaf
    Node(long long v)
        : is_op(false), op('\0'), val(v), left(nullptr), right(nullptr) {}

    // operator node takes ownership of children
    Node(char o, std::unique_ptr<Node> l, std::unique_ptr<Node> r)
        : is_op(true), op(o), val(0), left(std::move(l)), right(std::move(r)) {}
};

std::unique_ptr<Node> parse_rpn_expression(const std::vector<std::string>& tokens);
long long evaluate_tree(const Node* root);
std::string pretty_print(const Node* root);

// tracing
void set_trace_enabled(bool enabled);
