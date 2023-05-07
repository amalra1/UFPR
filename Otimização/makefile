CC = gcc
CFLAGS = -Wall -std=c99

# Arquivos objeto:
OBJ = DotLPMaker.o functions.o

producao: $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o producao

functions.o: functions.c functions.h
		$(CC) $(CFLAGS) -c functions.c

clean:
		rm *.o
        
purge: clean
		rm -f producao
