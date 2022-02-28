/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_print_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:11:19 by bkandemi          #+#    #+#             */
/*   Updated: 2022/02/25 14:18:46 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	putchar_nbyte(char c, int n)
{
	int	i = 0;

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
