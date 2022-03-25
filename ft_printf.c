/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:51:31 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/24 13:16:50 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	realloc_before_append(char **str)
{
	char	*new;

	new = (char *)ft_memalloc(ft_strlen(*str) + 2);
	new = ft_strcpy(new, *str);
	ft_strdel(str);
	*str = new;
}

static int	handle_format(const char *format, t_flag *flag, int *i, va_list ap)
{
	int	j;
	int	ret;

	j = 0;
	ret = 0;
	while (is_char_in_str(format[*i], VALID) == TRUE)
	{
		realloc_before_append(&(flag->str));
		flag->str[j++] = format[*i];
		if (is_char_in_str(format[*i], SPECS) == TRUE)
		{
			ret = put_format(flag, ap);
			reset(flag);
			break ;
		}
		*i = *i + 1;
	}
	return (ret);
}

static int	parse(const char *format, va_list ap)
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
			i--;
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
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = parse(format, ap);
	va_end(ap);
	return (ret);
}
