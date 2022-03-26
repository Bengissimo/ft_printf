/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_print_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:11:19 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/26 20:35:41 by bkandemi         ###   ########.fr       */
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
	if (nbyte < 0)
		nbyte = 0;
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
