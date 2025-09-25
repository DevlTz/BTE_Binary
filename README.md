# Binary Calculator (C++)

This repository contains a small C++ project that:
- Builds a **binary expression tree** representing arithmetic expressions in **Reverse Polish Notation (RPN / postfix) or Binary Calculator - As you prefer**.
- Evaluates the expression and prints the result to standard output.
- Provides basic error handling: invalid tokens, insufficient operands, division by zero.

## Repository structure

```
rpn_calc_cpp/
├─ src/
│  ├─ main.cpp
│  ├─ expr_tree.cpp
├─ include/
│  ├─ expr_tree.h
├─ examples/
│  ├─ example1.txt
├─ CMakeLists.txt
├─ Makefile
├─ run_example.sh
├─ README.md
├─ LICENSE
```

## Requirements

- A modern C++ compiler (recommended `g++` >= 9 or `clang++`).
- CMake (optional) for building.

## How to compile

### With g++
```bash
g++ -std=c++17 src/main.cpp src/expr_tree.cpp -o calc
```

### With Makefile
```
make
```

### With CMake
```bash
mkdir -p build
cd build
cmake ..
cmake --build .
```

## Usage
The program reads tokens provided as command-line arguments. Each token must be an integer (e.g., `3` or `-12`) or one of the operators `+ - * /`.

Examples:
```bash
./calc 1 2 + 3 *
# output: 9

./calc 5 1 2 + 4 * + 3 -
# equivalent to: 5 + ((1+2)*4) - 3 = 14
```

Note: When using shell wildcards like `*`, the shell may expand them before passing to the program. To avoid shell expansion for the asterisk operator, quote or escape it:
```bash
./calc 1 2 + 3 '*'
# or
./calc 1 2 + 3 \*
```

The program uses integer arithmetic (`long long`) and performs integer division (truncation toward zero). If you prefer floating-point arithmetic, modify `expr_tree.cpp` or open an issue.

## Getting started
1. Open `src/main.cpp` to see how command-line tokens are processed.
2. `include/expr_tree.h` and `src/expr_tree.cpp` implement the expression tree and evaluation.
3. Run `make` or compile directly with `g++`.
4. Test using the expressions in `examples/` or create your own.

## Useful links
- Reverse Polish notation (RPN): https://en.wikipedia.org/wiki/Reverse_Polish_notation
- Expression trees: https://en.wikipedia.org/wiki/Binary_expression_tree
- CMake tutorial: https://cmake.org/cmake/help/latest/guide/tutorial/index.html

## License
MIT — see `LICENSE`.
