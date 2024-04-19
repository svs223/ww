CC := clang
CFLAGS += -Wall -Wextra -Werror -g

.PHONY: clean
.PHONY: test

ww: ww.c
	$(CC) $(CFLAGS) ww.c -o ww

tests/test-1.txt:
	mkdir -p tests
	echo 1 12 123 1234 12345 123456 12345678 123456789 1234567890 123456789 12345678 1234567 123456 12345 1234 123 12 1 > tests/test-1.txt
	
test: ww tests/test-1.txt
	@echo First test
	
	@echo
	@./ww < tests/test-1.txt
	@echo
	
	@echo
	@echo Did it work?

clean:
	rm -rf *.o ww test
