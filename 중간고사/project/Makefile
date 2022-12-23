# 구현
CC = gcc
OBJS = capture.o context.o decode.o main.o match.o rule.o stats.o

main: $(OBJS)
	$(CC) -o main $(OBJS)

%.o: %.c %.h
	$(CC) -c $<

main.o: main.c common.h context.h
	$(CC) -c main.c

.PHONY: clean
clean:
	rm -f *.o main