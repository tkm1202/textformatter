CC = gcc

OBJS = mainmodule.o lex.o header.o tab.o strmanage.o linemanage.o ps.o

textformatter: $(OBJS)
	$(CC) -o $@ $(OBJS) -ll -Wall -g
