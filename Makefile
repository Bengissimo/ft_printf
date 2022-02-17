# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/31 11:00:37 by bkandemi          #+#    #+#              #
#    Updated: 2022/02/16 15:08:27 by bkandemi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

C_FILES = ft_printf.c\
		get_conversion_specifiers.c\
		print_functions.c

O_FILES = $(C_FILES:.c=.o)

CC = gcc

FLAGS = -c -Wall -Wextra -Werror

all : $(NAME)

$(NAME):
		@$(CC) $(FLAGS) $(C_FILES) 
		@ar rc $(NAME) $(O_FILES)
		
clean:
	@rm -f $(O_FILES)
 
fclean: clean
	@rm -f $(NAME)

re:	fclean all

	

