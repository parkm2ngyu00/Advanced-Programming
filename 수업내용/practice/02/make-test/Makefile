CC = gcc
CFLAGS = -Wall -O2
OBJS = test1.o test2.o main.o

# == #

# main: main.o test1.o test2.o
# 	gcc -o main test1.o test2.o main.o

# == #

main: $(OBJS)
	$(CC) $(CFLAGS) -o main $(OBJS)

# == #

# test1.o: test1.c test1.h
# 	gcc -c test1.c

# test2.o: test2.c test2.h
# 	gcc -c test2.c

# == #

# test1.o: test1.c test1.h
# 	$(CC) $(CFLAGS) -c test1.c

# test2.o: test2.c test2.h
# 	$(CC) $(CFLAGS) -c test2.c

# == #

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

# == #

# main.o: main.c test1.h test2.h
# 	gcc -c main.c

# == #

main.o: main.c test1.h test2.h
	$(CC) $(CFLAGS) -c main.c

# == #

.PHONY: clean
clean:
	rm -f *.o main
