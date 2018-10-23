CC=gcc
CFLAGS= -Wall -O2 -g -std=c99
LIBDIR=LIB/
INCLUDEDIR=INCLUDE/
OBJDIR=OBJ/
BINDIR=BIN/
SRCDIR=SRC/

all: $(BINDIR)main 

$(BINDIR)main: $(SRCDIR)main.c liblist.a libgraph.a libmenu.a
	$(CC) $(CFLAGS) $^ -o $@ -L. -llist -lgraph -lmenu

menu.o: $(LIBDIR)menu.c $(INCLUDEDIR)menu.h
	$(CC) -o $(OBJDIR)menu.o -c $(CFLAGS) $<


list.o: $(LIBDIR)list.c $(INCLUDEDIR)list.h
	$(CC) -o $(OBJDIR)list.o -c $(CFLAGS) $<

graph.o: $(LIBDIR)graph.c $(INCLUDEDIR)graph.h
	$(CC) -o $(OBJDIR)graph.o -c $(CFLAGS) $<
	
liblist.a: list.o
	ar cr $@ $(OBJDIR)list.o
	
libgraph.a: graph.o
	ar cr $@ $(OBJDIR)graph.o
	
libmenu.a: menu.o
	ar cr $@ $(OBJDIR)menu.o

clean:
	rm -f $(OBJDIR)*

mrproper: clean
	rm -f liblist.a
	rm -f libgraph.a
	rm -f libmenu.a
	rm -f $(BINDIR)*

