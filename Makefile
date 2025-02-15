# Compiler and flags
CC = gcc
INC_DIRS = $(shell find include -type d)
CFLAGS = -DNDEBUG -Wall -Wextra -std=c11 $(addprefix -I, $(INC_DIRS))

# Directories
SRC = src
OUT = dist
OBJ = obj
INC = include

# Automatically find all .c and .h files
SRCS = $(wildcard $(SRC)/**/*.c $(SRC)/*.c)
OBJS = $(SRCS:$(SRC)/%.c=$(OBJ)/%.o)
DEPS = $(OBJS:.o=.d)  # Dependency tracking for headers

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

# Compile source files into object files with dependency tracking
$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Include dependencies for incremental builds
-include $(DEPS)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean build artifacts
clean:
	rm -rf $(OUT) $(OBJ)

# Connect to the server
connect:
	nc 127.0.0.1 8080
