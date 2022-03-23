/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_print_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:11:19 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/23 09:18:16 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	putchar_nbyte(char c, int n)
{
	int	i;

	i = 0;
	if (n < 0)
		n = 0;
	while (i < n)
	{
		write(1, &c, 1);
		i++;
	}
	return (n);
}

int	putstr_nbyte(char const *s, int nbyte)
{
	return (write(1, s, nbyte));
}

int	is_char_in_str(char c, char *str)
{
	int	i;
	int	found;

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

void	initiate(t_flag *flag)
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

void	reset(t_flag *flag)
{
	ft_strdel(&(flag->str));
	initiate(flag);
}
