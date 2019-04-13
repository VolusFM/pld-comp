# yottacompilatron9001
**yottacompilatron9001** is a compiler for a subset of C.

## Building
Simply execute `make` in the project's root folder.
`make grammar` produces the ANTLR classes with the CodeC.g4 grammar.
`make objs` compile the ANTLR classes.
`make compile` produces the runnable binary file.
`make clean` removes all compiled classes and the binary.

Options are:
  * `grammar` : builds the grammar
  * `objs` : compiles the grammar
  * `compile` : builds the compiler
  * `clean` : removes generated files

## Usage
Syntax: `yottacompilatron9001 <input.c> [-a] [-o] [-c [<output.s>]]`

The command line arguments are:
  * `-a` : enables static analysis.
  * `-o` : enables (basic) optimizations.
  * `-c` : produces assembly code output. If no output file is given, the assembly code is printed on stdout by default.
  
Running the compilator with an invalid syntax or on a file which does not respect the syntax described in CodeC.g4 will cause the process to terminate with an error.

## Test framework

Our tests are described in the **tests** folder.

To run tests, simply run `cd tests && ./mktests.sh`. The results will be printed on stdout and stored in results.csv.

## Demos

The demo folder contains several example C files to showcase the features of our compilator. The title of these files are self-explainatory.
The input.c file in the root folder is another example file that can be compiled with yottacompilatron9001.