# A Makefile for our project

C11 = cc -std=c11
CFLAGS = -Wall -pedantic -Werror -lm

PROJECT = trove
HEADERS = $(PROJECT).h
OBJ = trove.o global.o findfiles.o filenames.o indexing.o remove.o trovefile.o update.o words.o

$(PROJECT) : $(OBJ)
	$(C11) $(CFLAGS) -o $(PROJECT) $(OBJ) 

%.o:%c $(HEADERS)
	$(C11) $(CFLAGS) -c $<

clean:
	rm -f $(PROJECT) $(OBJ)
	rm -f $(OBJ)