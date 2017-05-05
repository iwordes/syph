/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 15:07:52 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/05 16:35:00 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define C req->cmp
#define CMP1 (tab_field(tab, C[i].id))
#define CMP2 (ent + tab_foff(tab, C[i].id))
#define CSIZE (tab_field(tab, C[i].id)->len * tab_field(tab, C[i].id)->size)

static bool		comp_(t_tab *tab, U8 *ent, t_req33 *req)
{
	t_cmpfn	cmp;
	U8		*val;
	U8		i;

	i = ~0;
	val = req->cmp_val;
	while (++i < req->cmp_len)
	{
		if ((cmp = sy_cmp(req->cmp[i].op)) == NULL)
			return (false);
		if (!cmp(CMP1, CMP2, val))
			return (false);
		val += CSIZE;
	}
	return (true);
}

void	tab_delete(t_tab *tab, U8 *ent, t_req33 *req)
{
	if (req->cnt < req->limit && comp_(tab, ent, req))
	{
		LOG("0x33 Deleting...");
		bzero(ent, tab->ent_size);
		req->cnt += 1;
	}
}
