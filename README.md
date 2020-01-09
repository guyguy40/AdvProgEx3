# Milestone 1

## Purpose

A C++ interpreter which is able to run simple scripts for the FlightGear flight simulator.

## Structure

**main.cpp** contains the main code for the program.

**lexer.h/cpp** converts an entire file (represented by a string) to a vector of lines, which are themselves vectors of tokens. Said tokens are to later be read and processed by the program.

**symbolTable.h/cpp** contains code for the program's symbol table - the table which holds all of the variables for the program and their values.

**math.h/cpp** processes mathematical expressions with or without variables such as (x+y)\*5. It is mostly code from the first assignment.

**commands.h/cpp** contains code for the various commands the program uses, such as printing, sleeping, and variable assignment.

**parser.h/cpp** iterates over the lines produced by the lexer, fetches the correct command from each line and runs it.
