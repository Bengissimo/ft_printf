# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/31 11:00:37 by bkandemi          #+#    #+#              #
#    Updated: 2022/03/22 13:49:36 by bkandemi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

C_FILES = ft_printf.c\
		get_flags.c\
		print_functions.c\
		helper_print_functions.c\
		handle_precision_flags.c\
		handle_width_flags.c\
		handle_other_flags.c\
		print_float.c\
		print_int.c\

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

	

