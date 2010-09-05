TOOLPREFIX=arm-none-linux-gnueabi-
CC=$(TOOLPREFIX)gcc
CFLAGS+=-O2 -Wall -W -g -s "-I../PDKfiles/include" "-I../PDKfiles/include/SDL" -L../PDKfiles/device/lib
LFLAGS=-lSDL -lSDL_image -lSDL_mixer -lpdl -Wl,--allow-shlib-undefined -L../PDKfiles/device/lib
SRCS= \
	SFont.c \
	board.c \
	bonus.c \
	game.c \
	graphics.c \
	main.c \
	menu.c \
	myutils.c \
	score.c
OBJS=$(SRCS:.c=.o)

all: gemz

gemz:	$(OBJS)
	$(TOOLPREFIX)gcc $(CFLAGS) -o $@ $(LFLAGS) $(OBJS)

clean:
	rm -f $(OBJS)
	rm -f *.bb *.gcov *.bbg *.da
	rm -f *~ ./core
	rm gemz
