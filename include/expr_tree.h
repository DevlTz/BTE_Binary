#pragma once

#include <string>
#include <vector>
#include <memory>

// Node (operator or value) using unique_ptr for children
struct Node {
    bool is_op;                 // True if this node is an operator, false if it's a value (leaf)
    char op;                    // Operator character (e.g., '+', '-', '*', '/'), valid if is_op == true
    long long val;              // Value stored in the node, valid if is_op == false
    std::unique_ptr<Node> left; // Pointer to the left child node (for binary operators)
    std::unique_ptr<Node> right;// Pointer to the right child node (for binary operators)

    // Constructor for leaf node (value)
    Node(long long v)
        : is_op(false), op('\0'), val(v), left(nullptr), right(nullptr) {}

    // Constructor for operator node, takes ownership of child nodes
    Node(char o, std::unique_ptr<Node> l, std::unique_ptr<Node> r)
        : is_op(true), op(o), val(0), left(std::move(l)), right(std::move(r)) {}
};

// Parses a calculator expression into an expression tree
std::unique_ptr<Node> parse_calculator_expression(const std::vector<std::string>& tokens);

// Evaluates the expression tree and returns the result
long long evaluate_tree(const Node* root);

// Returns a pretty-printed string representation of the expression tree
std::string pretty_print(const Node* root);

// Enables or disables tracing for debugging 
void set_trace_enabled(bool enabled);

