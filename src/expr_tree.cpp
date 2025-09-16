#include "../include/expr_tree.h"
#include <vector>
#include <stack>
#include <stdexcept>
#include <sstream>
#include <cctype>

static bool is_operator(const std::string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/";
}

Node* parse_rpn_expression(const std::vector<std::string>& tokens) {
    std::stack<Node*> st;
    for (const auto& t : tokens) {
        if (is_operator(t)) {
            if (st.size() < 2) {
                throw std::runtime_error("Erro: operadores sem operandos suficientes");
            }
            Node* right = st.top(); st.pop();
            Node* left = st.top(); st.pop();
            Node* opnode = new Node(t[0], left, right);
            st.push(opnode);
        } else {
            // parse integer (allow negative)
            size_t idx = 0;
            try {
                long long v = std::stoll(t, &idx);
                if (idx != t.size()) {
                    throw std::invalid_argument("token nao e inteiro completo");
                }
                Node* valnode = new Node(v);
                st.push(valnode);
            } catch (const std::exception& e) {
                throw std::runtime_error(std::string("Token invalido: ") + t);
            }
        }
    }
    if (st.empty()) {
        throw std::runtime_error("Expressao vazia");
    }
    Node* root = st.top(); st.pop();
    if (!st.empty()) {
        throw std::runtime_error("Expressao invalida: sobram tokens na pilha");
    }
    return root;
}

long long evaluate_tree(const Node* root) {
    if (!root) throw std::runtime_error("No nulo na avaliacao");
    if (!root->is_op) return root->val;
    long long L = evaluate_tree(root->left);
    long long R = evaluate_tree(root->right);
    switch (root->op) {
        case '+': return L + R;
        case '-': return L - R;
        case '*': return L * R;
        case '/':
            if (R == 0) throw std::runtime_error("Divisao por zero");
            return L / R; // integer division truncates toward zero
        default:
            throw std::runtime_error("Operador desconhecido");
    }
}

void free_tree(Node* root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    delete root;
}

// Optional: pretty print infix with parentheses
static void pretty_print_rec(const Node* n, std::ostringstream& out) {
    if (!n) return;
    if (!n->is_op) {
        out << n->val;
        return;
    }
    out << '(';
    pretty_print_rec(n->left, out);
    out << ' ' << n->op << ' ';
    pretty_print_rec(n->right, out);
    out << ')';
}

std::string pretty_print(const Node* root) {
    std::ostringstream out;
    pretty_print_rec(root, out);
    return out.str();
}
