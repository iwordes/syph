/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foff.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 11:09:46 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/05 23:34:36 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define F ((t_field*)(&tab->schema_len + 1))
#define SIZE (F[i].size * F[i].len)

off_t	tab_foff(t_tab *tab, U8 id)
{
	off_t	off;
	U8		i;

	LOG("\e[95mtab_foff\e[0m");
	i = ~0;
	off = 0;
	if (tab->schema_len != 0)
		id %= tab->schema_len;
	while (++i < id)
		off += SIZE;
	LOG("\e[92mtab_foff\e[0m");
	return (off);
}
