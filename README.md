# simple-translator

simple-translator is a C program that translates a simple language with scopes, declarations, and uses.
This program implements a simple lexical analyzer and predictive parser with semantic actions to do its job.

## Context-free grammar

Source language:
```
blocks -> blocks block | e
block -> '{' decls stmts '}'
decls -> decls decl | e
decl -> type id ;
stmts -> stmts stmt | e
stmt ->  block | id ;
```

Output language:
```
blocks -> blocks block | e
block -> '{' stmts '}'
stmts -> stmts stmt | e
stmt -> block | id ':' type ;
```

## Example

Input:
```
{int hello; int world; hello; world; {bool hello; hello;} hello;}
```
Output:
```
{hello:int;world:int;{hello:bool;}hello:int;}
```

## Installation

You need to have `CMake version 3.10 or higher` and `a C compiler` installed to compile simple-translator.

```
mkdir build
cd build
cmake ..
cmake --build .
```

## Usage

```
./translator input_file.txt
```

