CC=gcc
CFLAGS= -Wall -O2 -g -std=c99
SRCDIR=LIB
INCLUDEDIR=INCLUDE
SRC=$(SRCDIR)/*.c
INCLUDE=$(INCLUDEDIR)/*.h
OBJDIR=OBJ/
TARGET=main
all: main

main: main.o  liblist.a libgraph.a
	$(CC) $(CFLAGS) -o $@ $<

main.o: main.c
	$(CC) -o $(OBJDIR)main.o -c $(CFLAGS) $<

list.o: $(SRCDIR)/list.c $(INCLUDEDIR)/list.h
	$(CC) -o $(OBJDIR)list.o -c $(CFLAGS) $<

graph.o: $(SRCDIR)/graph.c $(INCLUDEDIR)/graph.h
	$(CC) -o $(OBJDIR)graph.o -c $(CFLAGS) $<

liblist.a: list.o
	ar cr $@ $(OBJDIR)list.o
	
libgraph.a: graph.o
	ar cr $@ $(OBJDIR)graph.o

clean:
	rm -f $(OBJ)

mrproper: clean
	rm -f liblist.a
	rm -f libgraph.a

