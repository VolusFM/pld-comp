# yottacompilatron9001

**yottacompilatron9001** is a compiler for a subset of C.

It was desgined in a *modular* way and with *good memory management* practices in mind. Great aspects of this compiler is that it can generate code in two assembly langages (**x86** and **z80**), and that it doesn't leak memory while running (executing `valgrind` on it should display `all heap blocks were freed - no leaks are possible`; expect when it terminates due to bad input).

## Building

To build everything from the grammar to the compiler itself, simply execute `make` in the project's root folder.
To remove each file generated during the build, execute `make clean`.

The are other options to make only a step of the building process:
  * `make grammar` produces ANTLR classes from the CodeC.g4 grammar file.
  * `make objs` compiles ANTLR classes into object files.
  * `make compile` compiles all the project and produces the runnable binary file.

Additional settings are:
  * `make USE="shares"` to use the shared ANTLR distribution, located in /shares/public/tp/ANTLR4-CPP (default choice)
  * `make USE="local"` to use a local ANTLR distribution, located in ANTLR/"OS"-CPP where "OS" is LINUX, MAC or WINDOWS
  * `make FOR="DEV"` to produce the full (>5MB) compiler (instead of its stripped (~1MB) version), useful for debugging purposes

## Usage

Syntax: `yottacompilatron9001 <input.c> [-a] [-o] [-c [<output.s>]] [--x86 | --z80]`
Example: `yottacompilatron9001 input.c -c output.s` to compile `input.c` into `output.s`

The command line arguments are:
  * `-a` enables static analysis.
  * `-o` enables (basic) optimizations.
  * `-c` produces assembly code output. If no output file is given, the assembly code is printed on stdout by default.

It is also possible to specify the destination assembly langage by adding:
  * `--x86` to generate x86 assembly (default choice)
  * `--z80` to generate z80 assembly

Running the compilator with an invalid syntax or on a file which does not respect the either the syntax described in CodeC.g4 or the C semantics will cause the process to terminate with an error. An error message will be displayed, and the program will throw, which can result in a (deliberate) core dump.


## Test framework

Our tests are described in the **tests** folder.

To run tests, simply run `cd tests && ./mktests.sh`. The results will be printed on stdout and stored in tests/results.csv.


## Demos

The demo folder contains several example C files to showcase the features of our compilator. The title of these files are self-explainatory.
The input.c file in the root folder is another example file that can be compiled with yottacompilatron9001.

