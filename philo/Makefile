# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iportill <iportill@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/28 15:37:52 by iportill          #+#    #+#              #
#    Updated: 2023/12/29 12:17:39 by iportill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

SRCS =	main.c \
		utils.c

INCLUDE = philo.h \

CC = gcc
RM = rm -f
AR = ar rcs
CFLAGS = -Wall -Wextra -Werror -lpthread#-g3 -fsanitize=thread

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
