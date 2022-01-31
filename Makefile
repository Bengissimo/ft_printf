# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/31 11:00:37 by bkandemi          #+#    #+#              #
#    Updated: 2022/01/31 11:38:58 by bkandemi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

C_FILES = ft_printf.c

O_FILES = $(C_FILES:.c=.o)

CC = gcc

FLAGS = -Wall -Wextra -Werror

INCLUDES = -I . -I libft -L libft -lft -lftprintf

all : $(NAME)

$(NAME):
		@make -C libft/ fclean && make -C libft/
		@$(CC) $(FLAGS) -c $(C_FILES) 
		@ar rc $(NAME) $(O_FILES)
		
clean:
	@make clean -C libft
	@rm -f $(O_FILES)
 
fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)

re:	fclean all

test:
	

