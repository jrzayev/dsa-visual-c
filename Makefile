# Makefile for DSA Visual Library

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
TARGET = dsa_demo
SRC_DIR = src

SOURCES = $(SRC_DIR)/main.c \
          $(SRC_DIR)/linked_list.c \
          $(SRC_DIR)/stack.c \
          $(SRC_DIR)/queue.c \
          $(SRC_DIR)/binary_tree.c \
          $(SRC_DIR)/graph.c \
          $(SRC_DIR)/sorting.c \
          $(SRC_DIR)/searching.c \
          $(SRC_DIR)/utils.c

OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/dsa_visual.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

rebuild: clean all

help:
	@echo "DSA Visual Library - Makefile Commands:"
	@echo "  make          - Build the project"
	@echo "  make run      - Build and run the program"
	@echo "  make clean    - Remove build files"
	@echo "  make rebuild  - Clean and rebuild"
	@echo "  make help     - Show this help message"

.PHONY: all clean run rebuild help
