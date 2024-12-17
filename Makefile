# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

# Target executable
TARGET = dungeon_game

# Source files
SRCS = main.o player.o room.o creature.o item.o file_parser.o game.o menu.o

# Object files
OBJS = $(SRCS:.c=.o)

# Compile the project
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Clean build artifacts
clean:
	rm -f $(TARGET) $(OBJS)

# Individual object file compilation
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@




