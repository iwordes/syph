/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:29:20 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/03 11:33:53 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define A tu->req.asn
#define C tu->req.cmp

#define AV tu->req.asn_val
#define CV tu->req.cmp_val

#define ASN1 (tab_field(tab, A[i].id))
#define ASN2 (ent + tab_foff(tab, A[i].id))

#define CMP1 (tab_field(tab, C[i].id))
#define CMP2 (ent + tab_foff(tab, C[i].id))

#define ASIZE (tab_field(tab, A[i].id)->len * tab_field(tab, A[i].id)->size)
#define CSIZE (tab_field(tab, C[i].id)->len * tab_field(tab, C[i].id)->size)

void	tab_update(t_tab *tab, U8 *ent, t_tabupd *tu)
{
	U8		*val;
	U8		i;

	i = ~0;
	val = CV;
	while (++i < tu->req.cmp_len)
	{
		if (!tu->req.cmp[i](CMP1, CMP2, val))
			return ;
		val += CSIZE;
	}
	i = ~0;
	val = AV;
	while (++i < tu->req.asn_len)
	{
		tu->req.assign[i](ASN1, ASN2, val);
		val += ASIZE;
	}
}
