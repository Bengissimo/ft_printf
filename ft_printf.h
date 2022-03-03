/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:31:19 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/03 13:57:39 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include "libft_hive/libft.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h> //dont forget to delete
#include <wctype.h>
#include <stdint.h>

#define TRUE 1
#define FALSE 0

#define VALID_CHARS "#0-+ 123456789.hlLcspdiouxXf"
#define CONVERSIONS "cspdiouxXf"
#define INT_OR_OCTAL	"diouxX"
#define FLAGS		"0# +-"


typedef struct		s_flag
{
	char			*str;
	int				zero;
	int				hash;
	int				space;
	int				plus;
	int				dash;
	int				width;
	int				precision;
	char			length[2];
	char			specifier;
}					t_flag;

int		ft_printf(const char *format, ...);
void	parse(const char *format, va_list ap);
void	fill(t_flag *flag);
void	reset(t_flag *flag);
void	initiate(t_flag *flag);


int	putchar_nbyte(char c, int n);
int	putstr_nbyte(char const *s, int nbyte);
int	print_c(t_flag *flag, va_list ap);
int	print_s(t_flag *flag, va_list ap);
int	print_p(t_flag *flag, va_list ap);
int print_int(t_flag *flag, va_list ap);

void	put_format(t_flag *flag, va_list ap);

void	check_print(t_flag *flag); //to be deleted









#endif
