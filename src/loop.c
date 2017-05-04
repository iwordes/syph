/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 15:53:28 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/03 19:55:26 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

static t_op	g_op[] =
{
	{ 0x21, op_21_create },
	{ 0x2f, op_2f_delete },

	{ 0x30, op_30_insert },
	{ 0x31, op_31_select },
	{ 0x32, op_32_update },
	{ 0x33, op_33_delete },

	{ 0xff, op_ff_ping },

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
			sy_log("Failed to accept connection.");
		else
			tp_qpush(g_mn.tp, req_recv, (void*)in);
	}
}
