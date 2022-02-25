/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:40:33 by bkandemi          #+#    #+#             */
/*   Updated: 2022/02/25 11:12:50 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "ft_printf.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
	int nb = -8;
	char c = 'c';
	char *str = "abc";
	
	//ft_printf("Hello (%p)", p);
	
	//printf("(%-05d)\n", nb);
	printf("(%-+5d)", 8);
	write(1, &c, 5);
	return (0);
}


/*
for d or i
.  if precision > strlen, add leading (precision - strlen) zeros {
		if width > (precision) and no dash_flag, add (width - precision - strlen) leading space  
		if there is dash_flag add (width - precision - strlen) trailing space}
	else if precision <= strlen, print str.



*/