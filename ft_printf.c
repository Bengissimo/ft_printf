/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:51:31 by bkandemi          #+#    #+#             */
/*   Updated: 2022/02/17 10:07:15 by bkandemi         ###   ########.fr       */
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

static void	realloc_before_append(char **str)
{
	char	*new;
//think about if malloc fails
	new = (char *)malloc(sizeof(char) * (ft_strlen(*str) + 2));
	ft_strcpy(new, *str);
	ft_strdel(str);
	*str = new;
}

void	initiate(t_conv_spec *arg)
{
	arg->str = ft_memalloc(1);
	arg->specifier = '\0';
	arg->dash_flag= FALSE;
	arg->hash_flag= FALSE;
	arg->plus_flag= FALSE;
	arg->space_flag = FALSE;
	arg->zero_flag= FALSE;
	arg->width = 0;
	arg->precision = 0;
	ft_bzero(arg->length, 2);
}

static void	clean_up(char **str, int *flag)
{
	ft_strdel(str);
	if (*flag == TRUE)
		ft_putendl("specifier not found");
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
	initiate(&arg);
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
				reset(&arg);
			}
		}
		else
		{
			if (specifier == FALSE)
				ft_putchar(format[i]);
			else
			{
				realloc_before_append(&(arg.str));
				arg.str[j++] = format[i];
				if (is_specifier(format[i]) == TRUE)
				{
					specifier = FALSE;
					ft_putarg(&arg, ap);
				}
			}
		}
		i++;
	}
	clean_up(&(arg.str), &specifier);
}

int	ft_printf(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	parse(format, ap);
	va_end(ap);
	return (0);
}
