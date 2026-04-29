CC = gcc
CFLAGS = -Wall -g -ansi -pedantic -o $@
OBJECTS = preAssembler.o macro.o general.o main.o label.o errors.o utils.o firstPass.o DCimage.o ICimage.o secondPass.o writeFiles.o fileData.o

assembler: $(OBJECTS)
	$(CC) $(CFLAGS) $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<
	
clean:
	rm -f *.o
