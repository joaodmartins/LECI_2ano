#
# makefile to compile all programs for the AED.P07 computer lab class
#

clean:
	rm -f a.out binary_tree functionTests


binary_tree:	binary_tree.c elapsed_time.h
	cc -Wall -g binary_tree.c -o binary_tree -lm

functionTests:	functionTests.c elapsed_time.h
	cc -Wall -g functionTests.c -o functionTests -lm

