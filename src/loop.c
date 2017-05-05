/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 15:53:28 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/04 18:48:53 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

t_op		g_op[] =
{
	{ 0x21, op_21_create },
	/*
	** { 0x2f, op_2f_delete },
	*/

	{ 0x30, op_30_insert },
	{ 0x31, op_31_select },
	{ 0x32, op_32_update },
	{ 0x33, op_33_delete },

	{ 0xff, op_ff_ping },

	{ 0x00, NULL }
};

t_cmp		g_cmp[] =
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

	{ 0x00, NULL }
};

t_asn		g_asn[] =
{
	{ 0x50, op_50_set },

	/*
	** { 0x51, op_51_add },
	** { 0x52, op_52_sub },
	** { 0x53, op_53_mul },
	** { 0x54, op_54_div },
	** { 0x55, op_55_mod }
	*/

	{ 0x00, NULL }
};

static void	req_recv(void *fd)
{
	uint8_t	op;
	uint8_t	i;

	i = 0;
	read((int)fd, &op, 1);
	while (g_op[i].fn != NULL)
	{
		if (g_op[i].op == op)
		{
			g_op[i].fn((int)fd);
			break ;
		}
		i += 1;
	}
	close((int)fd);
}

void		loop(void)
{
	struct sockaddr_in	sa_inc;
	ssize_t				in;
	socklen_t			l;

	l = sizeof(sa_inc);
	while (1)
	{
		if ((in = accept(g_mn.sock, (void*)&sa_inc, &l)) < 0)
			sy_log("Could not accept connection.");
		else
		{
			sy_log("Connection established from: PLACEHOLDER");
			tp_qpush(g_mn.tp, req_recv, (void*)in);
		}
	}
}
