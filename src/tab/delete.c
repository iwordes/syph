/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 15:07:52 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/03 13:30:51 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define C td->req.cmp
#define CMP1 (tab_field(tab, C[i].id))
#define CMP2 (ent + tab_foff(tab, C[i].id))
#define CSIZE (tab_field(tab, C[i].id)->len * tab_field(tab, C[i].id)->size)

void	tab_delete(t_tab *tab, U8 *ent, t_tabdel *td)
{
	U8		*val;
	U8		i;

	i = ~0;
	val = td->req.cmp_val;
	while (++i < td->req.cmp_len)
	{
		if (!td->req.cmp[i](CMP1, CMP2, val))
			return ;
		val += CSIZE;
	}
	bzero(ent, tab->entry_size);
}
