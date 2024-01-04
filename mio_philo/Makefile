NAME = philo

SRCS =	main.c \
		error.c \
		create_thread_mutex.c \
		utils.c
		

INCLUDE = philo.h \

CC = gcc
RM = rm -f
AR = ar rcs
CFLAGS = -Wall -Wextra -Werror -lpthread -g3 #-fsanitize=thread

%.o: %.c ${INCLUDE}
			@echo "${BLUE} ◎ $(BROWN)Compiling   ${MAGENTA}→   $(CYAN)$< $(DEF_COLOR)"
			@${CC} ${CFLAGS} -c $< -o $@

OBJS = ${SRCS:.c=.o}

all:	${NAME}

${NAME}:	${OBJS}
			@$(CC) $(OBJS) $(CFLAGS) -o $(NAME)
			@echo "\n$(GREEN) Created $(NAME) ✓ $(DEF_COLOR)\n"

clean:
			@${RM} ${OBJS}
			@echo "\n${BLUE} ◎ $(RED)All objects cleaned successfully ${BLUE}◎$(DEF_COLOR)\n"

fclean:
			@${RM} ${OBJS}
			@${RM} ${NAME}
			@echo "\n${BLUE} ◎ $(RED)All objects and executable cleaned successfully${BLUE} ◎$(DEF_COLOR)\n"

re: fclean all

.PHONY: all clean fclean re
