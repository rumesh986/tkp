CC = gcc

FILE_BASE_NAME = libtkp
C_FILE = $(FILE_BASE_NAME).c
H_FILE = $(FILE_BASE_NAME).h
O_FILE = $(FILE_BASE_NAME).o
SO_FILE = $(FILE_BASE_NAME).so

.PHONY: compile build run
compile: $(C_FILE)
	$(CC) -c -fPIC $(C_FILE) -o $(O_FILE)

build: compile
	$(CC) -shared $(O_FILE) -o $(SO_FILE)

run: build
	./$(SO_FILE)

.PHONY: clean
clean:
	rm $(O_FILE) $(SO_FILE)
