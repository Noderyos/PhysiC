CFLAGS =-Wall -Wextra -Werror -Iinclude -Iraylib/include
LDFLAGS =-Lraylib/lib -l:libraylib.a -lm
all: src/main.c
	gcc $(CFLAGS) -o main $< $(LDFLAGS)
