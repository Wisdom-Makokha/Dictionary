# Makefile

# Compiler
CPPFLAGS = -Wall -Wextra -std=c++17

#HEADERS
HEADERS = definitions.h

#objects
OBJECTS = main.o UI\terminal_interface.o  functions\searching.o functions\entry_manipulation.o functions\display_entries.o functions\definitiontree.o

all: dictionary

# dictionary executable
dictionary: $(OBJECTS)
	gcc $(CPPFLAGS) -o dictionary $(OBJECTS)

#object compilation
main.o: definitions.h

UI\terminal_interface.o: definitions.h

functions\searching.o: definitions.h

functions\entry_manipulation.o: definitions.h

functions\display_entries.o: definitions.h

functions\definitiontree.o: definitions.h

clean:
	rm -f $(OBJECTS)