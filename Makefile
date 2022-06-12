CC= clang
CFLAGS= -I. -Wall

DIRS=build
$(shell mkdir -p $(DIRS))

forthvm :
	$(CC) $(CFLAGS) -c src/instructions.c -o build/instructions.o
	$(CC) $(CFLAGS) -c src/machine.c -o build/machine.o
	$(CC) $(CFLAGS) -c src/image.c -o build/image.o
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o
	$(CC) $(CFLAGS) -o forthvm build/main.o build/instructions.o build/machine.o build/image.o

clean :
	rm forthvm
	rm -rf build
