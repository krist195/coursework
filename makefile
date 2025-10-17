CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic
TARGET = main.o
SRC = main.c \
      header/fajl.c \
      header/pokaz.c \
      header/sortirovka.c \
      header/operacii.c \
      header/stroki.c

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
