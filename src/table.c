/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 19:31:59 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/04 23:43:27 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

/*
** Return a pointer to the head of a table.
*/

t_tab	*table(uint32_t id)
{
	uint32_t	(*tab)[2];
	size_t		i;

	dprintf(g_mn.log, "table(%u)\n", id);
	i = 0;
	tab = (void*)(DBH + 1);
	while (i < DBH->tab_cnt)
	{
		dprintf(g_mn.log, "table:       %d: %d\n", tab[i][0], tab[i][1]);
		if (tab[i][0] != 0 && tab[i][0] == id)
		{
			return ((void*)(DB.map + (tab[i][1] * 4096)));
		}
		i += 1;
	}
	return (NULL);
}
