/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 15:34:51 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/04 17:32:07 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define LEN (sizeof(g_cmp) / sizeof(t_cmp))

t_cmpfn		sy_cmp(uint8_t op)
{
	uint8_t		i;

	i = 0;
	while (i < LEN)
	{
		if (g_cmp[i].op == op)
			break ;
		i += 1;
	}
	return (g_cmp[i].fn);
}
