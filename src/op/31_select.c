/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <kdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 12:13:51 by kdavis            #+#    #+#             */
/*   Updated: 2017/06/22 11:38:54 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define END { LOG("\e[91m0x31\e[0m"); db_unlock(); return ; }

static void		pls_select(int sock, t_tab *tab, t_req31 *req)
{
	tab_foreach(tab, tab_match, req);
	write(sock, &req->cnt, 4);
	req->cnt = 0;
	req->sock = sock;
	tab_foreach(tab, tab_select, req);
}

/*
** 1. Lock the database for reading.
** 2. Attempt to read all necessary information from our socket.
** 3. If the client requests an invalid table, fail.
** 4. Get the comparisons the client wishes to use to limit results.
** 5. Select all matching entries, returning the count, then their data as req.
** 6. Unlock the database.
** 7. Free the memory used for matching comparisons.
*/

void			op_31_select(int sock)
{
	t_tab		*tab;
	t_req31		req;
	t_getpair	p;

	LOG("\e[95m0x31\e[0m Select");
	db_rlock();
	bzero(&req, sizeof(req));
	if (!sy_read(sock, &req, 9))
		END;
	if (!sy_read(sock, req.field, req.field_len))
		END;
	if ((tab = table(req.tid)) == NULL)
		END;
	p.tab = tab;
	p.sock = sock;
	if (!sy_getpair(p, req.cmp_len, req.cmp, &req.cmp_val))
		END;
	LOG("0x31 Selecting...");
	pls_select(sock, tab, &req);
	db_unlock();
	free(req.cmp_val);
	lprintf("[%.8s] \e[92m0x31\e[0m %u selected\n", sy_time(), req.cnt);
}
