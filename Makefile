CC=clang
CFLAGS=-std=c11 -Wall -Wextra -Werror -O2 -g
LDFLAGS=
SRC=src/main.c
BIN=kvstore

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -o $@ $(SRC) $(LDFLAGS)

clean:
	rm -f $(BIN)

.PHONY: all clean

