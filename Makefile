# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/31 11:00:37 by bkandemi          #+#    #+#              #
#    Updated: 2022/03/26 22:48:10 by bkandemi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

C_FILES = ft_printf.c\
		gather_flags.c\
		gather_precision.c\
		gather_width.c\
		handle_flags.c\
		handle_precision.c\
		handle_width.c\
		helper_functions.c\
		parse_format.c\
		print_char_str.c\
		print_float.c\
		print_int.c\
		put_format.c\
		round_float.c
		

O_FILES = $(C_FILES:.c=.o)

CC = gcc

FLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME):
	@make -C libft/ fclean && make -C libft/
	@$(CC) $(FLAGS) -c $(C_FILES)
	@cp libft/libft.a libftprintf.a
	@ar rc $(NAME) $(O_FILES)
	@ranlib $(NAME)
		
clean:
	@rm -f $(O_FILES)
	@make -C libft/ clean
 
fclean: clean
	@rm -f $(NAME)
	@make -C libft/ clean

re:	fclean all
