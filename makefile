# Variables
CC = gcc               # Compiler
CFLAGS = -Wall -g      # Compiler flags for warnings and debugging
SRC = main.c graph.c algorithms/bruteforce.c algorithms/backtracking.c experiment.c algorithms/smart_bruteforce.c algorithms/branchandbound.c
TARGET = clique_problem     # Final executable name

# Default target
run: $(TARGET)

# Compile and link directly into the executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $(SRC)

# Clean up generated files
clean:
	rm -f $(TARGET)

# Phony targets (to avoid file name conflicts)
.PHONY: all clean
