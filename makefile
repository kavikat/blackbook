#
# Makefile for blackbook
#
# Author: Kavika Tavui
#

project1: bbFunctions.o bb.o
	gcc -o p1 bbunctions.o bb.o

bbFunctions.o: bbFunctions.c record.h
	gcc -c -ansi -Wall bbFunctions.c

p1main.o: bb.c record.h
	gcc -c -ansi -Wall bb.c

.PHONY: clean
clean:
	rm -f cluster
	rm -f *.o
