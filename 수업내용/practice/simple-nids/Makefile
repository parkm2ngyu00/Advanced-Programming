.PHONY: all clean

CC = gcc

INC_DIR = include
SRC_DIR = main reception pool decoder rule detection log
OBJ_DIR = obj

CFLAGS = -g -Wall -std=gnu99 $(addprefix -I,$(shell find $(SRC_DIR) -type d)) -DDEBUG
LDFLAGS = -lpthread -lpcap

PROG = simple_nids

SRC = $(shell find $(SRC_DIR) -name '*.c')
OBJ = $(patsubst %.c, %.o, $(notdir $(SRC)))

vpath %.c $(dir $(SRC))
vpath %.o $(OBJ_DIR)

all: $(PROG)

$(PROG): $(addprefix $(OBJ_DIR)/, $(OBJ))
	mkdir -p $(@D)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(PROG) $(OBJ_DIR)
