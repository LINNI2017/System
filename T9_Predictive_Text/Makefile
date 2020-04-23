# LINNI CAI
# CSE 374 HOMEWORK 4
# 2017/11/09
# Makefile compiles files for T9.

T9: T9.o trie.o
	gcc -Wall -std=c11 -g T9.o trie.o -o T9

T9.o: trie.h T9.c
	gcc -Wall -std=c11 -g -c T9.c

trie.o: trie.c trie.h
	gcc -Wall -std=c11 -g -c trie.c

clean: 
	rm -f *.o T9 
