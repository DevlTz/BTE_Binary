#include "../include/expr_tree.h"
#include <vector>
#include <stack>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <cstdlib>

static bool TRACE = false;
void set_trace_enabled(bool enabled) { TRACE = enabled; }

static bool is_operator(const std::string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/";
}

long long evaluate_tree(const Node* root) {
    if (!root) throw std::runtime_error("Null node in evaluation");
    if (!root->is_op) return root->val;
    long long L = evaluate_tree(root->left.get());
    long long R = evaluate_tree(root->right.get());
    switch (root->op) {
        case '+': return L + R;
        case '-': return L - R;
        case '*': return L * R;
        case '/':
            if (R == 0) throw std::runtime_error("Division by zero");
            return L / R; // integer trunc towards zero
        default:
            throw std::runtime_error("Unknown operator");
    }
}

// pretty print infix with parentheses
static void pretty_print_rec(const Node* n, std::ostringstream& out) {
    if (!n) return;
    if (!n->is_op) {
        out << n->val;
        return;
    }
    out << '(';
    pretty_print_rec(n->left.get(), out);
    out << ' ' << n->op << ' ';
    pretty_print_rec(n->right.get(), out);
    out << ')';
}

std::string pretty_print(const Node* root) {
    std::ostringstream out;
    pretty_print_rec(root, out);
    return out.str();
}

std::unique_ptr<Node> parse_rpn_expression(const std::vector<std::string>& tokens) {
    std::stack<std::unique_ptr<Node>> st;

    for (const auto& t : tokens) {
        if (is_operator(t)) {
            if (st.size() < 2) {
                // stack unwinding via unique_ptr destructor -> no leak
                throw std::runtime_error("Error: operator without sufficient operands");
            }
            // pop right then left (move ownership)
            std::unique_ptr<Node> right = std::move(st.top()); st.pop();
            std::unique_ptr<Node> left  = std::move(st.top()); st.pop();

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
            // parse integer
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

    if (st.empty()) throw std::runtime_error("Empty expression");
    auto root = std::move(st.top()); st.pop();

    if (!st.empty()) {
        // leftover tokens -> invalid expr
        throw std::runtime_error("Invalid expression: leftover operands in stack");
    }
    return root; // ownership transferred to caller
}
