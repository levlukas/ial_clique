# Variables
CC = gcc               # Compiler
CFLAGS = -Wall -g      # Compiler flags for warnings and debugging
SRC = main.c graph.c   # Source files
TARGET = myprogram     # Final executable name

# Default target
all: $(TARGET)

# Compile and link directly into the executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $(SRC)

# Clean up generated files
clean:
	rm -f $(TARGET)

# Phony targets (to avoid file name conflicts)
.PHONY: all clean
