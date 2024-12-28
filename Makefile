LDFLAGS = -lncursesw 
CFLAGS = 
CC = gcc
VPATH = src:include:build

crogue: main.c keymapper.h keymapper.o mapper.h mapper.o
	$(CC) $(CFLAGS) $(LDFLAGS) -Iinclude $? -o $@

build/keymapper.o: keymapper.c
	$(CC) $(CFLAGS) $(LDFLAGS) -Iinclude -c $? -o $@

build/mapper.o: mapper.h mapper.c object.o
	$(CC) $(CFLAGS) $(LDFLAGS) -Iinclude -c $? -o $@

build/object.o: object.c
	$(CC) $(CFLAGS) $(LDFLAGS) -Iinclude -c $? -o $@

.PHONY: cleanall
cleanall:
	rm build/*.o crogue

.PHONY: rebuild
rebuild: cleanall crogue


