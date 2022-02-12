/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:51:31 by bkandemi          #+#    #+#             */
/*   Updated: 2022/02/12 23:04:02 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*static int	arg_count(const char *format)
{
	int	count;
	
	count = 0;

	while (*format != '\0')
	{
		if (*format == '%')
			count ++;
		format++;
	}
	return (count);	
}*/



static int	is_specifier(char c)
{
	int	i;

	i = 0;
	while (CONVERSIONS[i] != '\0')
	{
		if (c == CONVERSIONS[i])
			return (TRUE);
		i++;
	}
	return (FALSE);
}



static void	put_fmt_nbr(int nb)
{
	ft_putnbr(nb);
}

static void	check_print(t_conv_spec *arg)
{
	printf("str: %s\n", arg->str);
	printf("dash: %d, hash: %d, plus: %d, space: %d, zero: %d\n", arg->dash_flag, arg->hash_flag, arg->plus_flag, arg->space_flag, arg->zero_flag);
	printf("width: %d\n", arg->width_int);
	printf("precision: %d\n", arg->precision);
	printf("length[0]: %c, length[1]: %c\n", arg->length[0], arg->length[1]);
	printf("specifier: %c\n", arg->specifier);
}

void	ft_putarg(t_conv_spec *arg, va_list ap)
{
	fill(arg);
	check_print(arg);
	int nb;
	if (arg->specifier == 'd')
	{
		nb = va_arg(ap, int);
		put_fmt_nbr(nb);
	}
}

void	parse(const char *format, va_list ap)
{
	int		i;
	int		j;
	int		count;
	int		specifier;
	t_conv_spec arg;

	i = 0;
	j = 0;
	count  = 0;
	specifier = FALSE;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			if (specifier == TRUE)
				ft_putchar('%');
			else
			{
				specifier = TRUE;
				j = 0;
				count++;
				initiate(&arg);
			}
		}
		else
		{
			if (specifier == FALSE)
				ft_putchar(format[i]);
			else
			{
				arg.str[j++] = format[i]; // realloc_append fonksiyonu yaz
				if (is_specifier(format[i]) == TRUE)
				{
					specifier = FALSE;
					/*ft_putstr(tmp);
					ft_putchar('[');
					ft_putnbr(count);
					ft_putstr("]");*/
					ft_putarg(&arg, ap);
				}
			}
		}
		i++;
	}
	if (specifier == TRUE) //error case
	{
		ft_putendl("specifier not found");
	}
	
}

int	ft_printf(const char *format, ...)
{
	va_list ap;
	
	va_start(ap, format);
	parse(format, ap);
	//fn here
	
	va_end(ap);
	return (0);
}
