CC = gcc
LDFLAGS = -I/usr/local/include -L/usr/local/lib 
CFLAGS = -std=c99 -Wall
LIBS = -lallegro -lallegro_image -lallegro_font -lallegro_ttf -lallegro_primitives -lallegro_audio -lallegro_acodec
NAME = blocks
OBJ = blocks.o init.o gameplay.o draw.o swap.o timeUpdate.o menu.o scoreboard.o levelSelect.o gameOver.o

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS) $(LIBS) 

blocks.o: blocks.c structs.h
	$(CC) $(CFLAGS) -c blocks.c

init.o: init.c init.h structs.h gameplay.h
		$(CC) $(CFLAGS) -c init.c

gameplay.o: gameplay.c gameplay.h structs.h init.h
	$(CC) $(CFLAGS) -c gameplay.c

draw.o: draw.c draw.h structs.h init.h
	$(CC) $(CFLAGS) -c draw.c

swap.o: swap.c swap.h structs.h
	$(CC) $(CFLAGS) -c swap.c

timeUpdate.o: timeUpdate.c timeUpdate.h structs.h
	$(CC) $(CFLAGS) -c timeUpdate.c

Input.o: Input.c Input.c structs.h
	$(CC) $(CFLAGS) -c Input.c

menu.o: menu.c menu.h structs.h
	$(CC) $(CFLAGS) -c menu.c

scoreboard.o: scoreboard.c scoreboard.h structs.h
	$(CC) $(CFLAGS) -c scoreboard.c

levelSelect.o: levelSelect.c levelSelect.h structs.h
	$(CC) $(CFLAGS) -c levelSelect.c

gameOver.o: gameOver.c gameOver.h structs.h
	$(CC) $(CFLAGS) -c gameOver.c

clean:
	rm -f *.o

purge:
	rm -f *.o
	rm -f $(NAME)
