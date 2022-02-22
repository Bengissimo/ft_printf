/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:40:33 by bkandemi          #+#    #+#             */
/*   Updated: 2022/02/22 11:31:15 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "ft_printf.h"
#include <stdio.h>

int main(void)
{
	int nb = 8;
	//ft_printf("Hello (%p)", p);
	
	printf("(%010d)", nb);
	return (0);
}


/*
for d or i
.  if precision > strlen, add leading (precision - strlen) zeros {
		if width > (precision) and no dash_flag, add (width - precision - strlen) leading space  
		if there is dash_flag add (width - precision - strlen) trailing space}
	else if precision <= strlen, print str.



*/