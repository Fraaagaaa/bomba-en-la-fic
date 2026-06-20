CC = gcc
CFLAGS = -Wall

C_SOURCES = list.c p0.c
O_OBJECTS = $(C_SOURCES:.c=.o)
TARGET = a.out

all: $(TARGET)

$(TARGET): $(O_OBJECTS)
	$(CC) $(CFLAGS) $(O_OBJECTS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(O_OBJECTS)
	rm -f vgcore.*

run: $(TARGET)
	./$(TARGET)

val: $(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(TARGET)

