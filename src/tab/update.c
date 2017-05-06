/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:29:20 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/05 20:26:08 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define C req->cmp
#define CMP1 (tab_field(tab, C[i].id))
#define CMP2 (ent + tab_foff(tab, C[i].id))
#define CSIZE (tab_field(tab, C[i].id)->len * tab_field(tab, C[i].id)->size)

static bool		comp_(t_tab *tab, U8 *ent, t_req32 *req)
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

#define A req->asn
#define ASN1 (tab_field(tab, A[i].id))
#define ASN2 (ent + tab_foff(tab, A[i].id))
#define ASIZE (tab_field(tab, A[i].id)->len * tab_field(tab, A[i].id)->size)

static bool		assign_(t_tab *tab, U8 *ent, t_req32 *req)
{
	U8		*val;
	U8		i;

	i = ~0;
	val = req->asn_val;
	while (++i < req->asn_len)
		if (req->asn[i].id == 0 || sy_asn(req->asn[i].op) == NULL)
			return (false);
	i = ~0;
	while (++i < req->asn_len)
	{
		sy_asn(req->asn[i].op)(ASN1, ASN2, val);
		val += ASIZE;
	}
	return (true);
}

void			tab_update(t_tab *tab, U8 *ent, t_req32 *req)
{
	if (comp_(tab, ent, req) && assign_(tab, ent, req))
		req->cnt += 1;
}
