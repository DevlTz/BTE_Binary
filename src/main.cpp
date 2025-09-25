#include <bits/stdc++.h>
#include "../include/expr_tree.h"

int main(int argc, char** argv) {
    std::vector<std::string> tokens;
    if (argc <= 1) {
        std::string line;
        if (!std::getline(std::cin, line)) {
            std::cerr << "Usage: " << argv[0] << " <tokens RPN...> or pipe tokens via stdin\n";
            return 1;
        }
        std::istringstream iss(line);
        std::string tok;
        while (iss >> tok) tokens.push_back(tok);
    } else {
        for (int i = 1; i < argc; ++i) tokens.emplace_back(argv[i]);
    }

    set_trace_enabled(true);

    try {
        auto root = parse_rpn_expression(tokens); // unique_ptr<Node>
        long long result = evaluate_tree(root.get());
        std::cout << std::endl << "Final expression (infix): " << pretty_print(root.get()) << std::endl;
        std::cout << "Final result: " << result << std::endl;
        // no manual free needed
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 2;
    }
}
