#include <bits/stdc++.h>
#include "../include/expr_tree.h"

int main(int argc, char** argv) {
    if (argc <= 1) {
        std::cerr << "Uso: " << argv[0] << " <tokens RPN...>\n";
        std::cerr << "Ex: " << argv[0] << " 1 2 + 3 *\n";
        return 1;
    }
    std::vector<std::string> tokens;
    for (int i = 1; i < argc; ++i) tokens.emplace_back(argv[i]);

    try {
        Node* root = parse_rpn_expression(tokens);
        long long result = evaluate_tree(root);
        std::cout << result << std::endl;
        // optional: show the infix expression
        // std::cout << "infix: " << pretty_print(root) << std::endl;
        free_tree(root);
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 2;
    }
}
