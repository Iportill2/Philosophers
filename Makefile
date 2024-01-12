NAME = philo
CC = gcc
#CFLAGS = -Wall -Werror -Wextra  -g3 -fsanitize=thread #-pthread
CFLAGS = -Wall -Werror -Wextra  -g3 #-fsanitize=address #-pthread

CHECKER = checker
SRC_FILES = error.c \
			live.c \
			main.c \
			thread.c \
			watcher.c \
			utils.c


INCLUDE = philo.h


OBJS = $(SRC_FILES:.c=.o)

#.SILENT:

all: lib $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS)  $^

$(NAME): $(OBJS) $(INCLUDE)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re lib