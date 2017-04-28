/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 16:44:11 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/28 13:46:27 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>


static void	insert1(int sock, uint32_t tid, uint8_t f_len, uint8_t field[255])
{

}

void	op_32_insert(int sock)
{
	uint32_t	i;
	uint32_t	tid;
	uint32_t	e_len;
	uint8_t		f_len;
	uint8_t		field[255];

	read(sock, &tid, 4);
	tid = ntohl(tid);
	read(sock, &f_len, 1);
	read(sock, &field, f_len);

	// Single-Insert (placeholder) support
	insert1(sock, tid, f_len, field);

	// Multi-Insert support
	read(sock, &e_len, 4);
	e_len = recv_u32(sock);
	i = 0;
	while (i < e_len)
	{
		if (insert1(sock, tid, f_len, field) != 0)
		{
			error(/* ? */);
			return ;
		}
		i += 1;
	}
	send_u8();
}
