NOME = file_write

all: $(NOME).o
	ld -o $(NOME) $(NOME).o
	rm -rf *.o

%.o: %.asm
	nasm -f elf64 $<
