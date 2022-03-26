/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 20:31:07 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/26 20:39:32 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	initiate(t_flag *flag)
{
	flag->str = ft_memalloc(1);
	flag->spec = '\0';
	flag->dash = FALSE;
	flag->hash = FALSE;
	flag->plus = FALSE;
	flag->space = FALSE;
	flag->zero = FALSE;
	flag->width = 0;
	flag->dot = FALSE;
	flag->prec = 0;
	ft_bzero(flag->len, 2);
}

static void	realloc_before_append(char **str)
{
	char	*new;

	new = (char *)ft_memalloc(ft_strlen(*str) + 2);
	new = ft_strcpy(new, *str);
	ft_strdel(str);
	*str = new;
}

static void	reset(t_flag *flag)
{
	ft_strdel(&(flag->str));
	initiate(flag);
}

static int	handle_format(const char *format, t_flag *flag, int *i, va_list ap)
{
	int	j;
	int	ret;

	j = 0;
	ret = 0;
	if (format[*i] == '\0')
		return (ret);
	if (is_char_in_str(format[*i], VALID) == FALSE)
	{
		ft_putchar(format[*i]);
		return (ret + 1);
	}
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

int	parse(const char *format, va_list ap)
{
	t_flag	flag;
	int		ret;
	int		i;

	i = 0;
	ret = 0;
	initiate(&flag);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			ret = ret + handle_format(format, &flag, &i, ap);
		}
		else
		{
			ft_putchar(format[i]);
			ret++;
		}
		if (format[i] != '\0')
			i++;
	}
	ft_strdel(&(flag.str));
	return (ret);
}
