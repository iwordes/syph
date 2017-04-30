/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 19:31:59 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/29 20:24:07 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

/*
** Return a pointer to the head of a table.
*/

t_tbl_head	*table(uint32_t id)
{
	uint32_t(*)	tab[2];
	size_t		i;

	i = 0;
	tab = (void*)(g_mn.db.head + 1);
	while (i < g_mn.db.head.table_cnt)
	{
		if (tab[i][0])
			return ((void*)(g_mn.db.map + (tab[i][1] * 4096)));
		i += 1;
	}
}
