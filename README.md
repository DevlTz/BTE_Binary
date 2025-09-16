# RPN Calculator (C++)

Este repositório contém um pequeno projeto em C++ que:
- Constrói uma **árvore binária** representando expressões aritméticas em **notação polonesa reversa (RPN / pós-fixada)**.
- Avalia a expressão e imprime o resultado na saída padrão.
- Tratamento de erros básicos: tokens inválidos, operandos insuficientes, divisão por zero.

## Estrutura do repositório

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

## Requisitos

- Compilador C++ moderno (recomendo `g++` >= 9 ou `clang++`).
- CMake (opcional) para build.

## Como compilar

### Com g++
```bash
g++ -std=c++17 src/main.cpp src/expr_tree.cpp -o calc
```

### Com Makefile
```
make
```

### Com CMake
```bash
mkdir -p build
cd build
cmake ..
cmake --build .
```

## Uso
O programa lê tokens passados por argumentos na linha de comando. Cada token deve ser um inteiro (ex: `3` ou `-12`) ou um operador `+ - * /`.

Exemplos:
```bash
./calc 1 2 + 3 *
# output: 9

./calc 5 1 2 + 4 * + 3 -
# equivalente a: 5 + ((1+2)*4) - 3 = 14
```

O programa mantém aritmética inteira (tipo `long long`) e faz divisão inteira (truncamento em direção a zero). Se quiser aritmética em ponto flutuante, comente no issue ou modifique `expr_tree.cpp`.

## Onde começar
1. Abra `src/main.cpp` para ver a lógica de processamento dos argumentos.
2. `include/expr_tree.h` e `src/expr_tree.cpp` implementam a árvore e a avaliação.
3. Rode `make` ou compile diretamente com `g++`.
4. Teste com as expressões em `examples/` ou crie suas próprias.

## Links úteis
- Notação polonesa reversa (RPN): https://en.wikipedia.org/wiki/Reverse_Polish_notation
- Árvores de expressão: https://en.wikipedia.org/wiki/Binary_expression_tree
- Guia de CMake: https://cmake.org/cmake/help/latest/guide/tutorial/index.html

## Licença
MIT — veja `LICENSE`.
