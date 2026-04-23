#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 1
#
# make        makes Client
# make clean  removes all binaries and object files
#------------------------------------------------------------------------------

MAIN    = Client
MAINSRC = $(MAIN).c
MAINOBJ = $(MAIN).o

ADT     = List
ADTSRC  = $(ADT).c
ADTOBJ  = $(ADT).o
ADT_H   = $(ADT).h

GRAPH     = Graph
GRAPHSRC  = $(GRAPH).c
GRAPHOBJ  = $(GRAPH).o
GRAPH_H   = $(GRAPH).h

COMPILE = gcc -std=c17 -Wall -c
LINK    = gcc -std=c17 -Wall -o
REMOVE  = rm -f

# Build executable
$(MAIN): $(MAINOBJ) $(ADTOBJ) $(GRAPHOBJ)
	$(LINK) $(MAIN) $(MAINOBJ) $(ADTOBJ) $(GRAPHOBJ)

# Compile main
$(MAINOBJ): $(ADT_H) $(GRAPH_H) $(MAINSRC)
	$(COMPILE) $(MAINSRC)

# Compile List ADT
$(ADTOBJ): $(ADT_H) $(ADTSRC)
	$(COMPILE) $(ADTSRC)

# Compile Graph ADT
$(GRAPHOBJ): $(GRAPH_H) $(GRAPHSRC)
	$(COMPILE) $(GRAPHSRC)

# Clean
clean:
	$(REMOVE) $(MAIN) $(MAINOBJ) $(ADTOBJ) $(GRAPHOBJ)