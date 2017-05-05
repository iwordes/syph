/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpair.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 16:25:05 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/05 16:08:33 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define F (tab_field(p.tab, pair[i].id))

bool	sy_getpair(t_getpair p, U8 len, t_pair pair[255], U8 **val)
{
	size_t	mem;
	U8		i;

	lprintf("[%ld] \e[95msy_getpair\e[0m(%hhu)\n", time(NULL), len);
	i = ~0;
	mem = 0;
	*val = NULL;
	if (!sy_read(p.sock, pair, len * 2))
	{
		LOG("\e[91msy_getpair\e[0m");
		return (false);
	}
	while (++i < len)
		mem += F->size * F->len;
	if (mem != 0 && (*val = ZALT(U8, mem)) == NULL)
	{
		ERROR("Out of memory!");
		LOG("\e[91msy_getpair\e[0m");
		return (false);
	}
	if (mem != 0 && !sy_read(p.sock, *val, mem))
	{
		free(*val);
		LOG("\e[91msy_getpair\e[0m");
		return (false);
	}
	LOG("\e[92msy_getpair\e[0m");
	return (true);
}
