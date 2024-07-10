# Makefile

# Compiler
CFLAGS = -Wall -Wextra

#SOURCES
SOURCES = main.c UI\terminal_interface.c functions\storage_handling.c functions\searching.c functions\entry_manipulation.c functions\display_entries.c functions\definitiontree.c
#HEADERS
HEADERS = definitions.h

#objects
OBJECTS = main.o UI\terminal_interface.o  functions\storage_handling.o functions\searching.o functions\entry_manipulation.o functions\display_entries.o functions\definitiontree.o

all: dictionary

# dictionary executable
dictionary: $(OBJECTS)
	gcc $(CFLAGS) -o dictionary $(OBJECTS)

#object compilation
main.o: definitions.h

UI\terminal_interface.o: definitions.h

functions\storage_handling.o: definitions.h

functions\searching.o: definitions.h

functions\entry_manipulation.o: definitions.h

functions\display_entries.o: definitions.h

functions\definitiontree.o: definitions.h

clean:
	rm -f $(OBJECTS)