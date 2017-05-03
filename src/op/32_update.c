/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   32_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 15:38:54 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/03 11:18:02 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

static t_cmp	g_cmp =
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

#define REQ tu.req

#define E1 { db_unlock(); return ; }
#define E2 { db_unlock(); free(REQ.cmp_val); return ; }

void		op_32_update(int sock)
{
	t_tabupd	tu;
	t_getpair	p;

	bzero(&tu, sizeof(tu));
	sy_read(sock, &REQ, 6);
	db_wlock();
	p.sock = sock;
	if ((p.tab = table(REQ.tid)) == NULL)
		E1;
	if (sy_getpair(p, REQ.cmp_len, &REQ.cmp, &REQ.cmp_val))
		E1;
	if (sy_getpair(p, REQ.asn_len, &REQ.asn, &REQ.asn_val))
		E2;
	tab_foreach(p.tab, tab_update, &tu);
	db_unlock();
	write(sock, &tu.cnt, 4);
	free(REQ.cmp_val);
	free(REQ.asn_val);
}
