# Makefile

# Compiler
CFLAGS = -Wall -Wextra

#SOURCES
SOURCES = main.c UI\terminal_interface.c functions\definitiontree.c functions\storage_handling.c

#HEADERS
HEADERS = definitions.h

#objects
OBJECTS = main.o UI\terminal_interface.o functions\definitiontree.o functions\storage_handling.o

all: dictionary

# dictionary executable
dictionary: $(OBJECTS)
	gcc $(CFLAGS) -o dictionary $(OBJECTS)

#object compilation
main.o: definitions.h

UI\terminal_interface.o: definitions.h

clean:
	rm -f $(OBJECTS)