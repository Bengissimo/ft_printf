/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:31:19 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/23 10:49:10 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include "libft/libft.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h> //dont forget to delete
#include <wctype.h>
#include <stdint.h>

#define TRUE 1
#define FALSE 0

#define LIMIT 10000000000000000

#define VALID_CHARS "#0-+ 123456789.hlLcspdiouxXf%"
#define SPECS		"cspdiouxXf%"
#define INT			"diouxX"
#define UINT		"ouxXp"
#define FLAGS		"0# +-"


typedef struct		s_flag
{
	char			*str;
	int				zero;
	int				hash;
	int				space;
	int				plus;
	int				dash;
	uintmax_t		width;
	uintmax_t		prec;
	char			len[2];
	char			spec;
	int				dot;
}					t_flag;

int		ft_printf(const char *format, ...);
void	fill(t_flag *flag);
void	reset(t_flag *flag);
void	initiate(t_flag *flag);


int	putchar_nbyte(char c, int n);
int	putstr_nbyte(char const *s, int nbyte);
int	is_char_in_str(char c, char *str);


int	handle_char(t_flag *flag, char c);
int	print_c(t_flag *flag, va_list ap);
int	print_s(t_flag *flag, va_list ap);
int	print_p(t_flag *flag, va_list ap);
int	handle_int(t_flag *flag, char *str, int negative);
int	print_signed_int(t_flag *flag, va_list ap);
int	print_unsigned_int(t_flag *flag, va_list ap);
int	print_double(t_flag *flag, va_list ap);

/* get_flags */
void	fill_specifier(t_flag *flag);
void	fill_flags(t_flag *flag);
void	fill_width(t_flag *flag);
void	fill_precision(t_flag *flag);
void	fill_len_mod(t_flag *flag, char c);

/* handle_other_flags.c */
int	handle_plus_or_space(t_flag *flag, char *str, int negative);
intmax_t handle_length_mod(t_flag *flag, va_list ap);
intmax_t handle_unsigned_length_mod(t_flag *flag, va_list ap); //p'yi ekleyince adi kotu oldu

/* handle_width_flags.c */
int handle_width(t_flag *flag, char *str, int negative);
//int handle_width_zero(t_flag *flag, char *str, int negative);
int handle_width_dash(t_flag *flag, char *str, int negative);


/* handle_precision */
int	handle_precision(t_flag *flag, char *str, int negative);
int	handle_width_precision_dash(t_flag *flag, char *str, int negative);
int	handle_width_precision(t_flag *flag, char *str, int negative);




int	put_format(t_flag *flag, va_list ap);



#endif
