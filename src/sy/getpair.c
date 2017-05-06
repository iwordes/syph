/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpair.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 16:25:05 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/05 16:56:42 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define F (tab_field(p.tab, pair[i].id))

bool	sy_getpair(t_getpair p, U8 len, t_pair pair[255], U8 **val)
{
	size_t	mem;
	U8		i;

	i = ~0;
	mem = 0;
	*val = NULL;
	if (!sy_read(p.sock, pair, len * 2))
		return (false);
	while (++i < len)
		mem += F->size * F->len;
	if (mem != 0 && (*val = ZALT(U8, mem)) == NULL)
	{
		ERROR("Out of memory!");
		return (false);
	}
	if (mem != 0 && !sy_read(p.sock, *val, mem))
	{
		free(*val);
		return (false);
	}
	return (true);
}
