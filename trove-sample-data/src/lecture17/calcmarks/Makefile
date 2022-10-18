calcmarks : calcmarks.o globals.o readmarks.o correlation.o
	cc -std=c99 -Wall -pedantic -Werror -o calcmarks \
		calcmarks.o globals.o readmarks.o correlation.o -lm


calcmarks.o : calcmarks.c calcmarks.h
	cc -std=c99 -Wall -pedantic -Werror -c calcmarks.c

globals.o : globals.c calcmarks.h
	cc -std=c99 -Wall -pedantic -Werror -c globals.c

readmarks.o : readmarks.c calcmarks.h
	cc -std=c99 -Wall -pedantic -Werror -c readmarks.c

correlation.o : correlation.c calcmarks.h
	cc -std=c99 -Wall -pedantic -Werror -c correlation.c

clean:
	rm -f *.o calcmarks
