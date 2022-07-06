CC=gcc
NAME=termcord
SRC=termcord.c
OBJ=*.o
TERMCORD_LIB=-Iinclude -Lsrc -ltermcord
CFLAGS=-Wall -Wextra -Werror -Wdeprecated -Wno-comment -pedantic -g -O0
VALGRIND_LOGS_FILE=valgrind-out.txt
GDB_TMP_FILES=.gdb_history peda-session-*.txt
LIBS=-lcurl

all: $(NAME)

valgrind: $(NAME)
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=$(VALGRIND_LOGS_FILE) ./$(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(TERMCORD_LIB) $(LIBS)

$(OBJ): src/libtermcord.a
	$(CC) $(CFLAGS) -c $(SRC) $(TERMCORD_LIB) $(LIBS)

src/libtermcord.a:
	make -C src/

clean:
	rm -f $(OBJ) $(GDB_TMP_FILES)
	make -C src/ clean

fclean: clean
	rm -f $(NAME) $(VALGRIND_LOGS_FILE)
	make -C src/ fclean

re: fclean all

.PHONY: all clean fclean re
