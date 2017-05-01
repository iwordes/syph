/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   32_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 15:38:54 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/30 17:36:44 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

static t_cmp	g_camp =
{
	{ 0x40, op_40_equ },
	{ 0x41, op_41_neq },

	/*
	** { 0x42, op_42_les },
	** { 0x43, op_43_leq },
	** { 0x44, op_44_gre },
	** { 0x45, op_45_geq },
	**
	** { 0x4e, op_4e_and },
	** { 0x4f, op_4f_or },
	*/
};

static t_asn	g_asn =
{
	{ 0x50, op_50_set }

	/*
	** { 0x51, op_51_add },
	** { 0x52, op_52_sub },
	** { 0x53, op_53_mul },
	** { 0x54, op_54_div },
	** { 0x55, op_55_mod }
	*/
};

void		op_32_update(int sock)
{
	t_req32	req;
	U32		cnt;
	U32		i;

	sy_read(sock, &req, 6);

	db_wlock();
	i = 0;
	while (/* ... */)
	{
		if (/* cmp */)
			cnt += 1;
		i += tab->entry_size;
	}
	write(sock, &cnt, 4);
	i = 0;
	while (/* ... */)
	{
		if (/* cmp */)
			/* write_fields */(sock, ent, &req);
		i += tab->entry_size;
	}
	db_unlock();
}
