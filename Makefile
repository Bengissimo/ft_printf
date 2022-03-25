# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/31 11:00:37 by bkandemi          #+#    #+#              #
#    Updated: 2022/03/25 14:41:48 by bkandemi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

C_FILES = ft_printf.c\
		get_flags.c\
		print_functions.c\
		helper_print_functions.c\
		handle_precision.c\
		handle_width.c\
		handle_other_flags.c\
		print_float.c\
		print_int.c\
		round_float.c

O_FILES = $(C_FILES:.c=.o)

CC = gcc

FLAGS = -Wall -Wextra -Werror

RUN_LIB = make -C libft/ fclean && make -C libft/

all : $(NAME)

$(NAME):
	@$(RUN_LIB)
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
