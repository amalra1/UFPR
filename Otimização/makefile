CC = gcc
CFLAGS = -Wall -std=c99

# Arquivos objeto:
OBJ = DotLPMaker.o functions.o

DotLPMaker: $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o DotLPMaker

functions.o: functions.c functions.h
		$(CC) $(CFLAGS) -c functions.c

clean:
		rm *.o
        
purge: clean
		rm -f DotLPMaker
