/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:29:20 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/04 17:45:26 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define A req->asn
#define C req->cmp

#define AV req->asn_val
#define CV req->cmp_val

#define ASN1 (tab_field(tab, A[i].id))
#define ASN2 (ent + tab_foff(tab, A[i].id))

#define CMP1 (tab_field(tab, C[i].id))
#define CMP2 (ent + tab_foff(tab, C[i].id))

#define ASIZE (tab_field(tab, A[i].id)->len * tab_field(tab, A[i].id)->size)
#define CSIZE (tab_field(tab, C[i].id)->len * tab_field(tab, C[i].id)->size)

static bool		comp_(t_tab *tab, U8 *ent, t_req32 *req)
{
	t_cmpfn	cmp;
	U8		*val;
	U8		i;

	i = ~0;
	val = CV;
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

static bool		assign_(t_tab *tab, U8 *ent, t_req32 *req)
{
	U8		*val;
	U8		i;

	i = ~0;
	val = AV;
	while (++i < req->asn_len)
		if (sy_asn(req->asn[i].id) == NULL)
			return (false);
	i = ~0;
	while (++i < req->asn_len)
	{
		sy_asn(req->asn[i].id)(ASN1, ASN2, val);
		val += ASIZE;
	}
	return (true);
}

void	tab_update(t_tab *tab, U8 *ent, t_req32 *req)
{
	if (comp_(tab, ent, req) && assign_(tab, ent, req))
		req->cnt += 1;
}
