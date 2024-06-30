build:
	gcc -g -o td ./src/*.c ./src/*.h -std=c99 -lm -Wall -Wextra -Wunused -lraylib
run:
	./td 
debug:
	valgrind ./td
clean:
	rm td
