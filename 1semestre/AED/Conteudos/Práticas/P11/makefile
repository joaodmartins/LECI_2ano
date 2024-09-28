

CC = gcc
CC_FLAGS = -g
OBJS = graph.o problema.o utils.o

.c.o:
	$(CC) $(CC_FLAGS) -c $<

problema: $(OBJS)
	$(CC) -o problema $(OBJS)

clean:
	rm *.o
	rm problema