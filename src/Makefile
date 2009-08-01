all: janec ast
	@echo "All done"

CC=gcc
CFLAGS=-Wall -I../include

ast: ast.o astval.o astop.o compile.o
	$(CC) -o $@ $+ -lgc

janec: y.tab.c lex.yy.c astval.o astop.o compile.o
	$(CC) -o $@ $+ -lgc

lex.yy.c: ../spec/jane.l
	flex $<

y.tab.c: ../spec/jane.y
	yacc -d $<


clean:
	rm -f lex.yy.c
	rm -f y.tab.*
	rm -f *.o
	rm -f jane
	rm -f ast


