CC := clang
CFLAGS += -Wall -Wextra -Werror -g

ww: ww.c
	$(CC) $(CFLAGS) ww.c -o ww

clean:
	rm -rf *.o ww
