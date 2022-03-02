/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:51:31 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/01 14:20:39 by bkandemi         ###   ########.fr       */
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

void	initiate(t_flag *flag)
{
	flag->str = ft_memalloc(1);
	flag->specifier = '\0';
	flag->dash= FALSE;
	flag->hash= FALSE;
	flag->plus= FALSE;
	flag->space = FALSE;
	flag->zero = FALSE;
	flag->width = 0;
	flag->precision = 0;
	ft_bzero(flag->length, 2);
}

/*static void	clean_up(t_flag *flag)
{
	flag->specifier = '\0';
	flag->dash= FALSE;
	flag->hash= FALSE;
	flag->plus= FALSE;
	flag->space = FALSE;
	flag->zero = FALSE;
	flag->width = 0;
	flag->precision = 0;
	ft_bzero(flag->length, 2);
	ft_strdel(&(flag->str));
}*/

void	parse(const char *format, va_list ap)
{
	int		i;
	int		j;
	int		count;
	int		specifier;
	t_flag flag;

	i = 0;
	j = 0;
	count  = 0;
	specifier = FALSE;
	initiate(&flag);
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
				reset(&flag);
			}
		}
		else
		{
			if (specifier == FALSE)
				ft_putchar(format[i]);
			else
			{
				realloc_before_append(&(flag.str));
				flag.str[j++] = format[i];
				if (is_specifier(format[i]) == TRUE)
				{
					specifier = FALSE;
					put_format(&flag, ap);
				}
			}
		}
		i++;
	}
	//clean_up(&(flag.str), &specifier);
	reset(&flag);
	//free(flag.str); //FIX HERE 
	//flag.str = NULL;
}

int	ft_printf(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	parse(format, ap);
	va_end(ap);
	return (0);
}
