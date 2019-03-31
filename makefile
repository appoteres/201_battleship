OBJS = boardgen.o engine.o
OPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g -std=c99

build: $(OBJS) main.c
	gcc $(LOPTS) $(OBJS) main.c -lncurses -o game 

boardgen.o: boardgen.c boardgen.h
	gcc $(OPTS) boardgen.c

engine.o: engine.c engine.h
	gcc $(OPTS) engine.c

clean: 
	rm -f $(OBJS) game