# Makefile

# Compiler
CFLAGS = -Wall -Wextra

#SOURCES
SOURCES = main.c UI\terminal_interface.c

#HEADERS
HEADERS = definitions.h

#objects
OBJECTS = main.o UI\terminal_interface.o

all: dictionary

# dictionary executable
dictionary: $(OBJECTS)
	gcc $(CFLAGS) -o dictionary $(OBJECTS)

#object compilation
main.o: definitions.h

UI\terminal_interface.o: definitions.h

clean:
	rm -f $(OBJECTS)