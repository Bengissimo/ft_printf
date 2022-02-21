/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:07:09 by bkandemi          #+#    #+#             */
/*   Updated: 2022/02/21 14:18:36 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*static void	check_print(t_conv_spec *arg)
{
	printf("str: %s\n", arg->str);
	printf("dash: %d, hash: %d, plus: %d, space: %d, zero: %d\n", arg->dash_flag, arg->hash_flag, arg->plus_flag, arg->space_flag, arg->zero_flag);
	printf("width: %d\n", arg->width);
	printf("precision: %d\n", arg->precision);
	printf("length[0]: %c, length[1]: %c\n", arg->length[0], arg->length[1]);
	printf("specifier: %c\n", arg->specifier);
}*/

static void	put_fmt_nbr(int nb)
{
	ft_putnbr(nb);
}


void	ft_putarg(t_conv_spec *arg, va_list ap)
{
	fill(arg);
	//check_print(arg);
	int nb;
	if (arg->specifier == 'd')
	{
		nb = va_arg(ap, int);
		if (arg->plus_flag == TRUE && nb >= 0)
		{
			ft_putchar('+');
		}
		put_fmt_nbr(nb);
	}
	else if (arg->specifier == 'c')
		print_c(arg, ap);
	else if (arg->specifier == 's')
		print_s(arg, ap);
	else if (arg->specifier == 'p')
		print_p(arg, ap);
		
}

static int	print_repeated(char c, int count)
{
	int i = 0;
	while (i < count)
	{
		ft_putchar(c);
		i++;
	}
	return (i);
}

int	print_c(t_conv_spec *arg, va_list ap)
{
	char c;

	c = va_arg(ap, int);
	if (arg->width < 1)
	{
		ft_putchar(c);
		return (1);
	}
	if (arg->dash_flag == TRUE)
	{
		ft_putchar(c);
		print_repeated(' ', arg->width - 1);
		return (1);
	}
	print_repeated(' ', arg->width - 1);
	ft_putchar(c);
	return (1);
}

static int	ft_putstr_nbyte(char const *s, int nbyte)
{
	int i;

	i = 0;
	while (s[i] != '\0' && i < nbyte)
	{
		ft_putchar(s[i]);
		i++;
	}
	return (i);
}

int	print_s(t_conv_spec *arg, va_list ap)
{
	char	*s;
	int		len;

	s = va_arg(ap, char *);
	len = ft_strlen(s);
	if (arg->precision == TRUE)
		len = arg->precision;
	if (arg->width <= len)
		return (ft_putstr_nbyte(s, len));
	if (arg->dash_flag == TRUE) // width > len
		return(ft_putstr_nbyte(s, len) + print_repeated(' ', arg->width - len));
	return (print_repeated(' ', arg->width - len) + ft_putstr_nbyte(s, len));
}

int print_p(t_conv_spec *arg, va_list ap)
{
	void	*ptr;
	char	*str;
	int		strlen;

	ptr = va_arg(ap, void *);
	str = ft_itoa_base((long)ptr, 16);
	strlen = ft_strlen(str);
	if (arg->width < strlen)
	{
		ft_putstr("0x");
		ft_putstr(str);
	}
	return (ft_strlen(str) + 2);
}
