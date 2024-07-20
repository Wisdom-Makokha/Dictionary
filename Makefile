# Makefile

# Compiler
COMPILER = g++

# Compiler flags
CPPFLAGS = -Wall -Wextra -std=c++17

#HEADERS
HEADERS = definition/definitions.h

#objects
OBJECTS = main/main.o UI/terminal_interface.o  dictionary_functions/searching.o dictionary_functions/entry_manipulation.o 
OBJECTS += dictionary_functions/display_entries.o dictionary_functions/definitiontree.o

all: dictionary

# dictionary executable
dictionary: $(OBJECTS)
	$(COMPILER) $(CPPFLAGS) -o dictionary $(OBJECTS)

#object compilation
main.o: $(HEADERS)

UI\terminal_interface.o: $(HEADERS)

functions\searching.o: $(HEADERS)

functions\entry_manipulation.o: $(HEADERS)

functions\display_entries.o: $(HEADERS)

functions\definitiontree.o: $(HEADERS)

clean:
	rm -f $(OBJECTS)