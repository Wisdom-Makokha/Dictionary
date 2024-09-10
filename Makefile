# Makefile

# Compiler
COMPILER = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Wshadow -Wstrict-prototypes -Wconversion -Wunreachable-code

#HEADERS
HEADERS = $(wildcard headers/*.h)

#objects
SOURCES = main/main.c
SOURCES += $(wildcard dictionary_functions/*.c)
SOURCES += $(wildcard db_functions/*.c)
SOURCES += $(wildcard UI/*.c)

all: dictionary

# dictionary executable
dictionary: $(SOURCES)
	$(COMPILER) $(CFLAGS) -o dictionary $(SOURCES) $(HEADERS) -lodbc32 -luser32