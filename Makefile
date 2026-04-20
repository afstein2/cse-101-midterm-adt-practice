
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

COMPILE = gcc -std=c17 -Wall -c
LINK    = gcc -std=c17 -Wall -o
REMOVE  = rm -f

# Build executable
$(MAIN): $(MAINOBJ) $(ADTOBJ)
	$(LINK) $(MAIN) $(MAINOBJ) $(ADTOBJ)

# Compile main
$(MAINOBJ): $(ADT_H) $(MAINSRC)
	$(COMPILE) $(MAINSRC)

# Compile ADT
$(ADTOBJ): $(ADT_H) $(ADTSRC)
	$(COMPILE) $(ADTSRC)

# Clean
clean:
	$(REMOVE) $(MAIN) $(MAINOBJ) $(ADTOBJ)
