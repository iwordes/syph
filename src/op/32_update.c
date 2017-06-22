/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   32_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 15:38:54 by iwordes           #+#    #+#             */
/*   Updated: 2017/06/22 11:41:05 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define E1 { LOG("\e[91m0x32\e[0m"); db_unlock(); return ; }
#define E2 { LOG("\e[91m0x32\e[0m"); db_unlock(); free(req.cmp_val); return ; }

/*
** 1. Lock the database for writing.
** 2. Attempt to read 6 bytes from the socket.
** 3. If the client requests an invalid table, fail.
** 4. Get all comparisons and assignments to use for this request.
** 5. Update each valid entry.
** 6. Unlock the database.
** 7. Return the number of entries updated.
** 8. Free allocated memory.
*/

void	op_32_update(int sock)
{
	t_req32		req;
	t_getpair	p;

	LOG("\e[95m0x32\e[0m Update");
	bzero(&req, sizeof(req));
	db_wlock();
	if (!sy_read(sock, &req, 6))
		E1;
	p.sock = sock;
	if ((p.tab = table(req.tid)) == NULL)
		E1;
	if (!sy_getpair(p, req.cmp_len, req.cmp, &req.cmp_val))
		E1;
	if (!sy_getpair(p, req.asn_len, req.asn, &req.asn_val))
		E2;
	LOG("0x32 Updating...");
	tab_foreach(p.tab, tab_update, &req);
	db_unlock();
	write(sock, &req.cnt, 4);
	free(req.cmp_val);
	free(req.asn_val);
	lprintf("[%.8s] \e[92m0x32\e[0m %u updated\n", sy_time(), req.cnt);
}
