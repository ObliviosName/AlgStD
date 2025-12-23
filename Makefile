# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Wextra -O2

# Название exe
TARGET = main.exe

# Исходники
SOURCES = main.c \
	src/lab1/lab1.c \
	src/lab2/lab2.c \
	src/lab3/lab3.c \
	src/lab4/lab4.c \
	src/lab5/lab5.c

# Хедеры
HEADERS = src/lab1/lab1.h \
	src/lab2/lab2.h \
	src/lab3/lab3.h \
	src/lab4/lab4.h \
	src/lab5/lab5.h

# Правило сборки
$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

# Очистка
clean:
	del /Q $(TARGET)

.PHONY: clean
