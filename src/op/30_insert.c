/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 16:44:11 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/29 12:13:22 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

// Perform a single entry insertion on a table.

static int	insert1(int sock, t_req30 *req)
{
	// 1. Allocate (zeroed) space for new entry in table
	// ...

	// 2. Locate new entry
	id = /* tbl_ */;

	// 3. Overwrite entry with new values
	i = 0;
	while (i < req->field_len)
		/* tbl_set_raw */(req->tid, id, req->field[i++], sock);

	// 4. Update table next-vals

	return (0);
}

void	op_32_insert(int sock)
{
	t_req30		req;
	t_tbl_head	*tbl;
	uint32_t	i;


	// 1. Read request.
	// TODO: Error after all reads if any failed
	read(sock, &req.tid, 4);
	read(sock, &req.field_len, 1);
	read(sock, &req.field, req.field_len);
	read(sock, &req.entry_len, 4);


	// 2. Allocate space in table for new entries.
	if (tbl_grow(req.tid, req.entry_len) != 0)
	{
		error(/* ? */);
		return ;
	}


	// 3. Insert entries.
	i = 0;
	while (i < e_len)
	{
		tbl_write(sock, &req, table(req->tid)->len + i);
		i += 1;
	}

	// 4. Update the table metadata.
	table(req->tid)->next_id += req.entry_len;
	table(req->tid)->len += req.entry_len;

	// 3. Return the number of entries inserted.
	write(sock, &i, 4);
}
