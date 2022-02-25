/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:07:09 by bkandemi          #+#    #+#             */
/*   Updated: 2022/02/25 10:38:32 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*static void	check_print(t_flag *flag)
{
	printf("str: %s\n", flag->str);
	printf("dash: %d, hash: %d, plus: %d, space: %d, zero: %d\n", flag->dash, flag->hash, flag->plus, flag->space, flag->zero);
	printf("width: %d\n", flag->width);
	printf("precision: %d\n", flag->precision);
	printf("length[0]: %c, length[1]: %c\n", flag->length[0], flag->length[1]);
	printf("specifier: %c\n", flag->specifier);
}*/

static void	put_fmt_nbr(int nb)
{
	ft_putnbr(nb);
}


void	put_format(t_flag *flag, va_list ap)
{
	fill(flag);
	//check_print(flag);
	int nb;
	if (flag->specifier == 'd')
	{
		nb = va_arg(ap, int);
		if (flag->plus == TRUE && nb >= 0)
		{
			ft_putchar('+');
		}
		put_fmt_nbr(nb);
	}
	else if (flag->specifier == 'c')
		print_c(flag, ap);
	else if (flag->specifier == 's')
		print_s(flag, ap);
	else if (flag->specifier == 'p')
		print_p(flag, ap);
	else if (flag->specifier == 'd' || flag->specifier == 'i')
		print_d_i(flag, ap);
		
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

int	print_c(t_flag *flag, va_list ap)
{
	char c;

	c = va_arg(ap, int);
	if (flag->width < 1)
	{
		ft_putchar(c);
		return (1);
	}
	if (flag->dash == TRUE)
	{
		ft_putchar(c);
		print_repeated(' ', flag->width - 1);
		return (1);
	}
	print_repeated(' ', flag->width - 1);
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

int	print_s(t_flag *flag, va_list ap)
{
	char	*s;
	int		len;

	s = va_arg(ap, char *);
	len = ft_strlen(s);
	if (flag->precision == TRUE && flag->precision > len)
		len = flag->precision;
	if (flag->width <= len)
		return (ft_putstr_nbyte(s, len));
	if (flag->dash == TRUE) // width > len
		return(ft_putstr_nbyte(s, len) + print_repeated(' ', flag->width - len));
	return (print_repeated(' ', flag->width - len) + ft_putstr_nbyte(s, len));
}

int print_p(t_flag *flag, va_list ap)
{
	void	*ptr;
	char	*str;
	int		strlen;

	ptr = va_arg(ap, void *);
	str = ft_itoa_base((long)ptr, 16);
	strlen = ft_strlen(str);
	if (flag->width < strlen)
	{
		ft_putstr("0x");
		ft_putstr(str);
	}
	return (ft_strlen(str) + 2);
}
int print_int(t_flag *flag, va_list ap)
{
	int		nb;
	char	*str;
	int		len;
	
	nb = va_arg(ap, int);
	str = ft_itoa(nb);
	len  = ft_strlen(str);
	if (flag->precision == TRUE && flag->precision > len) //if precision true ignore 0 flag
	{
		if (flag->width > flag->precision)
		{
			if (flag->dash == TRUE)
			return (print_repeated('0', flag->width - len - 1) + ft_putstr_nbyte(str, len));
		}
		if (flag->dash == TRUE)
		

	}
	if (flag->width > len)
	{
		if (flag->dash == TRUE)
		{
			if (str[0] != '-' && flag->plus == TRUE)
				return (write(1, "+", 1) + ft_putstr_nbyte(str, len) + print_repeated(' ', flag->width - len - 1));
			if (str[0] != '-' && flag->space == TRUE)
				return (write(1, " ", 1) + ft_putstr_nbyte(str, len) + print_repeated(' ', flag->width - len - 1));
			return (ft_putstr_nbyte(str, len) + print_repeated(' ', flag->width - len));
		}
		if (flag->zero == TRUE)
		{
			if (str[0] != '-' && flag->plus == TRUE)
				return (write(1, "+", 1) + print_repeated('0', flag->width - len - 1) + ft_putstr_nbyte(str, len));
			if (str[0] != '-' && flag->space == TRUE)
				return (write(1, " ", 1) +  print_repeated('0', flag->width - len - 1) + ft_putstr_nbyte(str, len));
			return (print_repeated('0', flag->width - len) + ft_putstr_nbyte(str, len));
		}
		if (str[0] != '-' && flag->plus == TRUE)
			return (write(1, "+", 1) + print_repeated(' ', flag->width - len - 1) + ft_putstr_nbyte(str, len));
		return (print_repeated(' ', flag->width - len) + ft_putstr_nbyte(str, len));
	}
	if (str[0] != '-' && flag->plus == TRUE)
		return (write(1, "+", 1) + ft_putstr_nbyte(str, len));
	if (str[0] != '-' && flag->space == TRUE)
		return (write(1, " ", 1) + ft_putstr_nbyte(str, len));
	return (ft_putstr_nbyte(str, len));
}
