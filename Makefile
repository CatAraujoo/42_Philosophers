# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmatos-a <cmatos-a@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/19 15:09:22 by cmatos-a          #+#    #+#              #
#    Updated: 2025/03/21 11:25:13 by cmatos-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread

SRC = philo.c \
		dinner.c \
		actions.c \
		write.c \
		syncro_utils.c \
		getters_setters.c \
		ft_init.c \
		ft_parse.c \
		utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -pthread $(OBJ) -o $(NAME)
	@echo "Compilation completed successfully!"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(OBJ) $(NAME)
	@echo "Everything is clean!"

re: fclean all
	@echo "Recompilation completed successfully!"

.PHONY: all clean fclean re