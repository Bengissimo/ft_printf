/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:51:31 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/21 12:38:29 by bkandemi         ###   ########.fr       */
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

static void	clean_up(t_flag *flag)
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
}

/*int	parse(const char *format, va_list ap)
{
	int		i;
	int		j;
	int		count;
	int		specifier;
	t_flag	flag;
	int ret;

	i = 0;
	j = 0;
	count  = 0;
	specifier = FALSE;
	ret = 0;
	initiate(&flag);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			if (specifier == TRUE)
			{
				ft_putchar('%');
				ret++;
			}
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
			{
				ft_putchar(format[i]);
				ret++;
			}
			else
			{
				realloc_before_append(&(flag.str));
				flag.str[j++] = format[i];
				if (is_specifier(format[i]) == TRUE)
				{
					specifier = FALSE;
					ret = ret + put_format(&flag, ap);
				}
			}
		}
		i++;
	}
	//clean_up(&(flag.str), &specifier);
	reset(&flag); //TO DO: fix the leak HERE
	//free(flag.str);
	//flag.str = NULL;
	return (ret);
}*/

static int	is_valid_char(char c)
{
	int i;

	i = 0;
	while (VALID_CHARS[i] != '\0')
	{
		if (c == VALID_CHARS[i])
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static int	is_char_in_str(char c, char *str)  //copy of the fn in get_conv_spec.c va_stare
{
	int	i;
	int found;

	found = FALSE;
	i = 0;
	while (str[i] != '\0')
	{
		if (c == str[i])
		{
			found = TRUE;
			break ;
		}
		i++;
	}
	return (found);
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
		if (format[i] == '%')
		{
			i++;
			j = 0;
			while (TRUE)
			{
				if (is_valid_char(format[i]) == FALSE)
					break;
				realloc_before_append(&(flag.str));
				flag.str[j++] = format[i];
				if (is_char_in_str(format[i], CONVERSIONS) == TRUE)
				{
					ret = ret + put_format(&flag, ap);
					reset(&flag);
					break;
				}
				i++;
			}
			i++;
		}
		
		else
		{
			ft_putchar(format[i]);
			ret++;
			i++;
		}
		
	}
	clean_up(&flag);
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
