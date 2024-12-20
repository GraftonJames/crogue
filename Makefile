LDFLAGS = -lncurses
CFLAGS = -Wall -Wextra
CC = gcc
VPATH = src:include:build

crogue: main.c gamestate.h 
	$(CC) $(CFLAGS) $(LDFLAGS) -Iinclude $? -o $@

keymapper.o: keymapper.h gamestate.h 
	$(CC) $(CFLAGS) $(LDFLAGS) -Iinclude -c $? -o $@

gamestate.o: keymapper.h
	$(CC) $(CFLAGS) $(LDFLAGS) -Iinclude -c $? -o $@

