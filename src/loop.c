/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 15:53:28 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/29 13:18:56 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

#include <syph.h>
#define FD (int)fd

static t_op	g_op[] =
{
	{ 0x21, op_21_create },
	{ 0x2f, op_2f_delete },

	{ 0x30, op_30_insert },
	{ 0x31, op_31_select },
	{ 0x32, op_32_update },
	{ 0x33, op_33_delete },

	{ 0xff, op_ff_ping }
};

static void	req_recv(void *fd)
{
	uint8_t	buff;
	uint8_t	i;

	i = 0;
	read(FD, &buff, 1);
	while (g_op[i] != NULL)
	{
		if (g_op[i].op == op)
		{
			g_op[i].fn(FD);
			break ;
		}
		i += 1;
	}
	close(FD);
}

void		loop(void)
{
	int		in;

	while (1)
	{
		if ((in = accept(g_mn.sock, /* ... */, /* ... */)) < 0)
			sy_log("Failed to accept connection.");
		else
			tp_qpush(g_mn.tp, req_recv, in);
	}
}
