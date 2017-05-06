/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 15:53:28 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/05 19:14:38 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

t_op		g_op[] =
{
	{ 0x21, op_21_create },

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
	{ 0x00, NULL }
};

t_asn		g_asn[] =
{
	{ 0x50, op_50_set },
	{ 0x00, NULL }
};

static void	req_recv(void *fd)
{
	uint8_t	op;
	uint8_t	i;

	i = 0;
	if (read((int)fd, &op, 1) == 1)
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

#define IPB ((U8*)(&sa_inc.sin_addr.s_addr))
#define CON_MSG "\e[1m%d\e[0m.\e[1m%d\e[0m.\e[1m%d\e[0m.\e[1m%d\e[0m\n"
#define CON_MSG_OK "[%.8s] \e[1;92m⇩\e[0m " CON_MSG
#define CON_MSG_KO "[%.8s] \e[1;91m⇩\e[0m " CON_MSG

void		loop(void)
{
	struct sockaddr_in	sa_inc;
	ssize_t				in;
	socklen_t			l;

	l = sizeof(sa_inc);
	while (1)
	{
		if ((in = accept(g_mn.sock, (void*)&sa_inc, &l)) < 0)
			lprintf(CON_MSG_KO, sy_time(), IPB[0], IPB[1], IPB[2], IPB[3]);
		else
		{
			lprintf(CON_MSG_OK, sy_time(), IPB[0], IPB[1], IPB[2], IPB[3]);
			tp_qpush(g_mn.tp, req_recv, (void*)in);
		}
	}
}
