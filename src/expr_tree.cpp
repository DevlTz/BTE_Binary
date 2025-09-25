#include "../include/expr_tree.h"
#include <vector>
#include <stack>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <cstdlib>

// Global flag for enabling/disabling trace output
static bool TRACE = true;
void set_trace_enabled(bool enabled) { TRACE = enabled; }

// Helper function to check if a string is an operator
static bool is_operator(const std::string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/";
}

// Recursively evaluates the expression tree rooted at 'root'
long long evaluate_tree(const Node* root) {
    if (!root) throw std::runtime_error("Null node in evaluation");
    if (!root->is_op) return root->val; // Leaf node: return value
    long long L = evaluate_tree(root->left.get());  // Evaluate left subtree
    long long R = evaluate_tree(root->right.get()); // Evaluate right subtree
    switch (root->op) {
        case '+': return L + R;
        case '-': return L - R;
        case '*': return L * R;
        case '/':
            if (R == 0) throw std::runtime_error("Division by zero");
            return L / R; // Integer division
        default:
            throw std::runtime_error("Unknown operator");
    }
}

// Helper function for pretty-printing the tree in infix notation with parentheses
static void pretty_print_rec(const Node* n, std::ostringstream& out) {
    if (!n) return;
    if (!n->is_op) {
        out << n->val; // Print value for leaf node
        return;
    }
    out << '(';
    pretty_print_rec(n->left.get(), out); // Print left subtree
    out << ' ' << n->op << ' ';
    pretty_print_rec(n->right.get(), out); // Print right subtree
    out << ')';
}

// Public function to pretty-print the tree as a string
std::string pretty_print(const Node* root) {
    std::ostringstream out;
    pretty_print_rec(root, out);
    return out.str();
}

// Parses a Reverse Polish Notation (RPN) expression into an expression tree
std::unique_ptr<Node> parse_rpn_expression(const std::vector<std::string>& tokens) {
    std::stack<std::unique_ptr<Node>> st; // Stack to build the tree

    for (const auto& t : tokens) {
        if (is_operator(t)) {
            // Operator: pop two operands from stack
            if (st.size() < 2) {
                throw std::runtime_error("Error: operator without sufficient operands");
            }
            // Pop right then left operand (move ownership)
            std::unique_ptr<Node> right = std::move(st.top()); st.pop();
            std::unique_ptr<Node> left  = std::move(st.top()); st.pop();

            // Create new operator node and push to stack
            auto opnode = std::make_unique<Node>(t[0], std::move(left), std::move(right));
            if (TRACE) {
                try {
                    long long val = evaluate_tree(opnode.get());
                    std::cout << "Applied operator '" << t[0] << "' -> subtree: "
                              << pretty_print(opnode.get()) << " = " << val << std::endl;
                } catch (const std::exception& e) {
                    std::cout << "Applied operator '" << t[0] << "' -> subtree: "
                              << pretty_print(opnode.get()) << " (eval error: " << e.what() << ")" << std::endl;
                }
            }
            st.push(std::move(opnode));
        } else {
            // Operand: parse integer and push as leaf node
            size_t idx = 0;
            long long v = 0;
            try {
                v = std::stoll(t, &idx);
            } catch (...) {
                throw std::runtime_error(std::string("Invalid token: ") + t);
            }
            if (idx != t.size()) {
                throw std::runtime_error(std::string("Invalid token: ") + t);
            }
            auto valnode = std::make_unique<Node>(v);
            if (TRACE) std::cout << "Pushed value: " << v << std::endl;
            st.push(std::move(valnode));
        }
    }

    // After processing all tokens, stack should have exactly one node (the root)
    if (st.empty()) throw std::runtime_error("Empty expression");
    auto root = std::move(st.top()); st.pop();

    if (!st.empty()) {
        // If stack is not empty, expression was invalid
        throw std::runtime_error("Invalid expression: leftover operands in stack");
    }
    return root; // Return the root of the expression tree
}
