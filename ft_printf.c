/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:51:31 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/22 09:23:50 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


/*static int	is_specifier(char c)
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
}*/

static void	realloc_before_append(char **str)
{
	char	*new;
	new = (char *)ft_memalloc(ft_strlen(*str) + 2);
	new = ft_strcpy(new, *str);
	ft_strdel(str);
	*str = new;
}

void	initiate(t_flag *flag)
{
	flag->str = ft_memalloc(1);
	flag->specifier = '\0';
	flag->dash = FALSE;
	flag->hash = FALSE;
	flag->plus = FALSE;
	flag->space = FALSE;
	flag->zero = FALSE;
	flag->width = 0;
	flag->dot = FALSE;
	flag->precision = 0;
	ft_bzero(flag->length, 2);
}

void	reset(t_flag *flag)
{
	ft_strdel(&(flag->str));
	initiate(flag);
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
	flag->dot = 0;
	ft_bzero(flag->length, 2);
	ft_strdel(&(flag->str));
}*/


static int handle_format(const char *format, t_flag *flag, int *i, va_list ap)
{
	int j;
	int ret;

	j = 0;
	ret = 0;
	while (is_char_in_str(format[*i], VALID_CHARS) == TRUE)
	{
		realloc_before_append(&(flag->str));
		flag->str[j++] = format[*i];
		if (is_char_in_str(format[*i], CONVERSIONS) == TRUE)
		{
			ret = put_format(flag, ap);
			reset(flag);
			break;
		}
		*i = *i + 1;
	}
	return (ret);
}

int	parse(const char *format, va_list ap)
{
	t_flag	flag;
	int		ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = 0;
	initiate(&flag);
	while (format[i] != '\0')
	{
		if (format[i++] == '%')
			ret = ret + handle_format(format, &flag, &i, ap);
		else
		{
			ft_putchar(format[i]);
			ret++;
		}
		i++;
	}
	ft_strdel(&(flag.str));
	return (ret);
}

int	ft_printf(const char *format, ...)
{
	va_list ap;
	int ret;

	va_start(ap, format);
	ret = parse(format, ap);
	va_end(ap);
	return (ret);
}
