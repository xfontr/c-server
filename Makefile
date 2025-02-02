# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Directories
SRC = src
OUT = dist
OBJ = obj

# Automatically find all .c files and corresponding .o files
SRCS = $(wildcard $(SRC)/**/*.c $(SRC)/*.c)
OBJS = $(SRCS:$(SRC)/%.c=$(OBJ)/%.o)

# Target executable
TARGET = $(OUT)/main

# Default rule: Build and run
start: build run

# Build rule
build: $(TARGET)

# Link all object files to create the executable
$(TARGET): $(OBJS)
	@mkdir -p $(OUT)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files into object files
$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean build artifacts
clean:
	rm -rf $(OUT) $(OBJ)
