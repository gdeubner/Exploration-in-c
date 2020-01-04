all: seventh

seventh: seventh.c
	gcc -g -Werror -Wall -fsanitize=address -std=c11 seventh.c -oseventh
	
clean:
	rm -f seventh
