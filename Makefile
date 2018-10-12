CC=gcc
CFLAGS= -Wall -O2 -g -std=c99
LIBDIR=LIB/
INCLUDEDIR=INCLUDE/
OBJDIR=OBJ/
BINDIR=BIN/
SRCDIR=SRC/

all: $(BINDIR)main

$(BINDIR)main: $(OBJDIR)main.o  liblist.a libgraph.a
	$(CC) $(CFLAGS) -o $@ $<

$(OBJDIR)main.o: $(SRCDIR)main.c
	$(CC) -o $@ -c $(CFLAGS) $<

list.o: $(LIBDIR)list.c $(INCLUDEDIR)list.h
	$(CC) -o $(OBJDIR)list.o -c $(CFLAGS) $<

graph.o: $(LIBDIR)graph.c $(INCLUDEDIR)graph.h
	$(CC) -o $(OBJDIR)graph.o -c $(CFLAGS) $<

liblist.a: list.o
	ar cr $@ $(OBJDIR)list.o
	
libgraph.a: graph.o
	ar cr $@ $(OBJDIR)graph.o

clean:
	rm -f $(OBJDIR)*

mrproper: clean
	rm -f liblist.a
	rm -f libgraph.a
	rm -f $(BINDIR)*

