CC = gcc
CFLAGS = -O2
LDFLAGS = -lcsv
SRC = main.c minestats.c leaderboard.c html_generator.c csv_parser.c
OBJ = $(SRC:.c=.o)
TARGET = gen

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)