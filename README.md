# yottacompilatron9001
**yottacompilatron9001** is a compiler for a subset of C.

## Building
Simply execute `make`.

Options are:
  * `grammar` : builds the grammar
  * `objs` : compiles the grammar
  * `compile` : builds the compiler
  * `clean` : removes generated files

## Usage
Syntax: `yottacompilatron9001 <input.c> [-a] [-o] [-c [<output.s>]]`

The command line arguments are:
  * `-a` : enables static analysis
  * `-o` : enables (basic) optimizations
  * `-c` : produces assembly code output

