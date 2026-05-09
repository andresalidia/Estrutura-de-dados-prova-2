CC = gcc
CFLAGS = -I./include
SRC = src/main.c src/lista.c src/storage.c src/ui.c src/logica.c
OBJ = $(SRC:.c=.o)
TARGET = navegador.exe

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	del /f $(TARGET)
