CC = gcc
CFLAGS = -Wall

C_SOURCES = list.c process.c file.c memoryList.c auxiliar.c p3.c commandsp0.c commandsp1.c commandsp2.c commandsp3.c
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

shell: $(TARGET)
	./$(TARGET)

val: $(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(TARGET)

static: $(O_OBJECTS)
	$(CC) $(CFLAGS) -static $(O_OBJECTS) -o a_static

run-static: static
	./a_static
