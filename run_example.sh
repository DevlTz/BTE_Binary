#!/usr/bin/env bash
set -e
# Compile and run the example
g++ -std=c++17 src/main.cpp src/expr_tree.cpp -o calc
echo "Compilado com sucesso."
echo "Executando: ./calc 1 2 + 3 *"
./calc 1 2 + 3 *
