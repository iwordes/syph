/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:23:44 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/05 13:42:55 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define C req->cmp
#define F req->field

#define CMP1 (tab_field(tab, C[i].id))
#define CMP2 (ent + tab_foff(tab, C[i].id))

#define CSIZE (tab_field(tab, C[i].id)->len * tab_field(tab, C[i].id)->size)

static bool		comp_(t_tab *tab, U8 *ent, t_req31 *req)
{
	t_cmpfn	cmp;
	U8		*val;
	U8		i;

	i = ~0;
	val = req->cmp_val;
	while (++i < req->cmp_len)
	{
		if ((cmp = sy_cmp(req->cmp[i].id)) == NULL)
			return (false);
		if (!cmp(CMP1, CMP2, val))
			return (false);
		val += CSIZE;
	}
	return (true);
}

#define OBT_LOC (ent + tab_foff(tab, F[f]))
#define OBT_SIZE (tab_field(tab, F[f])->len * tab_field(tab, F[f])->size)

static bool		obtain_(t_tab *tab, U8 *ent, t_req31 *req)
{
	U8	f;

	f = ~0;
	while (++f < req->field_len)
	{
		lprintf("[%d] 0x31 Send[%u, %u]\n", time(NULL), tab_foff(tab, F[f]), OBT_SIZE);
		if (write(req->sock, OBT_LOC, OBT_SIZE) <= 0)
			return (false);
	}
	return (true);
}

void			tab_select(t_tab *tab, U8 *ent, t_req31 *req)
{
	if (req->cnt < req->limit && comp_(tab, ent, req) && obtain_(tab, ent, req))
		req->cnt += 1;
}
