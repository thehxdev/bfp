# BFP
Simple BrainFuck source code profiler for command frequency discovery. Useful for interpreter optimization.

## Build
By default, each individual token is counted. To count each consecutive sequence of tokens only once,
define the `UNIQUE_SEQ` preprocessor variable using the `-DUNIQUE_SEQ=1` compiler flag.
And... You need build instructions for a single `.c` file? :)

## Use
```bash
# You can pass multiple brainfuck source files
./a.out ./examples/*
```
