CC = gcc
CFLAGS = -g -O0
LDLIBS = -Wl,-rpath,../src/ -L../src/ -ltkp
# LDLIBS = -L /home/rumesh/repo/tkp/ -ltkp

FILE_BASE_NAME = test_tkp
C_FILE = $(FILE_BASE_NAME).c
H_FILE = $(FILE_BASE_NAME).h
O_FILE = $(FILE_BASE_NAME).o

$(O_FILE): $(C_FILE)
	$(CC) $(CFLAGS) -c $(C_FILE) -o $(O_FILE)

.PHONY: build run
build: $(O_FILE)
	$(CC) $(O_FILE) $(LDLIBS) -o $(FILE_BASE_NAME)

run: build
	./$(FILE_BASE_NAME)

.PHONY: clean
clean:
	rm $(O_FILE) $(FILE_BASE_NAME)
