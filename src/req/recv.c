/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 11:24:58 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/28 12:40:31 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void		req_recv(void *fd)
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
