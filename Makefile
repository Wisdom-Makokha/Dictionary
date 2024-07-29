# Makefile

# Compiler
COMPILER = gcc

# Compiler flags
CFLAGS = -Wall -Wextra

#HEADERS
HEADERS = $(wildcard headers/*.h)

#objects
SOURCES = main/main.c
SOURCES += $(wildcard dictionary_functions/*.c)
SOURCES += $(wildcard UI/*.c)

all: dictionary

# dictionary executable
dictionary: $(SOURCES)
	$(COMPILER) $(CFLAGS) -o dictionary $(SOURCES) $(HEADERS)