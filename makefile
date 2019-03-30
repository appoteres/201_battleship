OBJS = boardgen.o 
OPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g -std=c99

build: $(OBJS) main.c
	gcc $(LOPTS) $(OBJS) main.c -o game 

boardgen.o: boardgen.c boardgen.h
	gcc $(OPTS) boardgen.c

clean: 
	rm -f $(OBJS) connect