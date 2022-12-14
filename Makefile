# A Makefile for our project
C11 = cc -std=c11
CFLAGS = -Wall -pedantic -Werror

PROJECT = trove
HEADERS = $(PROJECT).h
OBJ = trove.o globals.o findfiles.o filenames.o indexing.o remove.o trovefile.o update.o words.o

$(PROJECT) : $(OBJ)
	$(C11) $(CFLAGS) -o $(PROJECT) $(OBJ) -lm

%.o:%c $(HEADERS)
	$(C11) $(CFLAGS) -c $<

clean:
	rm -f $(PROJECT) $(OBJ)
	rm -f $(OBJ)