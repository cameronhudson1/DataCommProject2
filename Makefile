# C Files
SOURCE1 = dvrouting.c
SOURCE2 = lsrouting.c
SOURCEG = graph.c

# Programs
PROG1 = dvrouting
PROG2 = lsrouting

# Input & Output
IN1 = DVInput.txt
IN2 = LSInput.txt

# Compiler
CC = gcc
CFLAGS = -std=c99 -pthread -Wall -pedantic -O1 -g
GSLFLAGS = -lgsl -lgslcblas
VALGRIND = valgrind --tool=memcheck --leak-check=yes --track-origins=yes

# Objects
OBJ1 = $(patsubst %.c, %.o, $(SOURCE1))
OBJ2 = $(patsubst %.c, %.o, $(SOURCE2))
OBJG = $(patsubst %.c, %.o, $(SOURCEG))

# Phonys for all make commands
.PHONY: all, mem, help, clean

# Compiles all files into binaries
all: $(PROG1) $(PROG2)

# Turns the first object file into a binary
$(PROG1): $(OBJ1) $(OBJG)
	@echo "Linking $(PROG1)"
	$(CC) $(CFLAGS) $(OBJ1) $(OBJG) -o $(PROG1)

# Turns the second object file into a binary
$(PROG2): $(OBJ2) $(OBJG)
	@echo "Linking $(PROG2)"
	$(CC) $(CFLAGS) $(OBJ2) $(OBJG) -o $(PROG2)

# Compiles all .c files into .o files
.c.o:
	@echo "Compiling $<"
	$(CC) $(CFLAGS) -c $<

# Runs valgrind test for the binary
mem: $(PROG1)
	@echo "Running Valgrind test on $(PROG1)"
	$(VALGRIND) ./$(PROG1) IN1
	$(VALGRIND) ./$(PROG2) IN2

# Shows help message for all available make commands
help: 
	@echo "  all     - Compiles and links all sources"
	@echo "  mem     - Runs Valgrind on each command"
	@echo "  clean   - Removes all temporary files"
	@echo "  help    - Displays this message!"

# Removes all objects, binarys, and output files
clean: 
	@echo "Removing all temporary files"
	-rm -f *.o
	-rm -f $(PROG1)
	-rm -f $(PROG2)
