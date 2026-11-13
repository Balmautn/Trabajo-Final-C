CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = simulador
OBJS = main.o simulador.o validaciones.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
