# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: catarina <catarina@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/19 15:09:22 by cmatos-a          #+#    #+#              #
#    Updated: 2025/05/13 14:46:26 by catarina         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=thread

SRC = philo.c \
		dinner.c \
		actions.c \
		write.c \
		check_status.c \
		utils.c \
		ft_init.c \
		ft_parse.c \

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