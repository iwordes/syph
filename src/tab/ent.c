/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 13:27:39 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/04 13:55:15 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

/*
** Get an entry by id.
** 0: First entry
** ~0: Last entry
*/

uint8_t		*tab_ent(t_tab *tab, uint32_t id)
{
	uint8_t		*ent;
	uint32_t	i;

	i = 0;
	ent = (U8*)tab + (tab->hd_blk * 4096);
	if (id == 0)
		return (ent);
	if (id == ~0)
		return (ent + tab->len * tab->ent_size);
	while (i < tab->len)
	{
		if (*(U32*)ent == id)
			break ;
		ent += tab->ent_size;
		i += 1;
	}
	return (ent);
}
