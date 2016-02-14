all: interpreter

interpreter: interpreter.cpp expTree.cpp token.cpp Tree.h expTree.h token.h
	g++ -Wall -Wextra -pedantic -O0 -g $^ -o $@