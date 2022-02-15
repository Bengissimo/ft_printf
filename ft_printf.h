/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:31:19 by bkandemi          #+#    #+#             */
/*   Updated: 2022/02/15 09:56:54 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include "libft/libft.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h> //dont forget to delete

#define TRUE 1
#define FALSE 0

#define VALID_CHARS "#0-+ 123456789.hlLcspdiouxXf"
#define CONVERSIONS "cspdiouxXf"
#define INT_OR_OCTAL	"diouxX"
#define FLAGS		"0# +-"


typedef struct		s_conv_spec
{
	char			*str;
	int				zero_flag;
	int				hash_flag;
	int				space_flag;
	int				plus_flag;
	int				dash_flag;
	int				width_int;
	int				precision;
	char			length[2];
	char			specifier;
}					t_conv_spec;

int		ft_printf(const char *format, ...);
void	parse(const char *format, va_list ap);
void	fill(t_conv_spec *arg);
void	reset(t_conv_spec *arg);
void	initiate(t_conv_spec *arg);






#endif
