/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpair.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 16:25:05 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/03 13:50:49 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define SIZE (f->size * f->len)

void	sy_getpair(t_getpair p, U8 len, t_op2 pair[255], U8 **val)
{
	size_t	mem;
	size_t	off;
	t_field	*f;
	U8		i;

	i = ~0;
	off = 0;
	mem = 4096;
	sy_read(p.sock, pair, len * 2);
	if ((*val = MALT(U8, 4096)) == NULL)
	{
		ERROR("OOM");
		return (1);
	}
	while (++i < len)
	{
		f = tab_field(p.tab, pair[i].id);
		if (off + SIZE >= mem && DRALT(*val, U8, mem *= 2) == NULL)
		{
			ERROR("OOM");
			return (2);
		}
		sy_read(p.sock, *val + off, SIZE);
		off += SIZE;
	}
	return (0);
}
