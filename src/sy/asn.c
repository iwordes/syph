/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asn.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 15:34:51 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/04 17:32:16 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define LEN (sizeof(g_asn) / sizeof(t_asn))

t_asnfn		sy_asn(uint8_t op)
{
	uint8_t		i;

	i = 0;
	while (i < LEN)
	{
		if (g_asn[i].op == op)
			break ;
		i += 1;
	}
	return (g_asn[i].fn);
}
