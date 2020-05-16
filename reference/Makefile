CC = gcc
CFLAGS = -g -O0

FILE_BASE_NAME = tkp
C_FILE = $(FILE_BASE_NAME).c
H_FILE = $(FILE_BASE_NAME).h
O_FILE = $(FILE_BASE_NAME).o

.PHONY: compile build run
compile: $(C_FILE)
	$(CC) $(CFLAGS) -c $(C_FILE) -o $(O_FILE)

build: compile
	$(CC) $(O_FILE) -o $(FILE_BASE_NAME)

run: build
	./$(FILE_BASE_NAME)

.PHONY: clean
clean:
	rm $(O_FILE) $(FILE_BASE_NAME)
