/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   33_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 15:01:40 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/05 16:37:27 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

void	op_33_delete(int sock)
{
	t_req33		req;
	t_getpair	p;

	sy_log("\e[95m0x33\e[0m Delete");

	bzero(&req, sizeof(req));
	sy_read(sock, &req, 9);
	db_wlock();

	LOG("0x33 table");

	p.tab = table(req.tid);
	p.sock = sock;
	if (!sy_getpair(p, req.cmp_len, req.cmp, &req.cmp_val))
	{
		db_unlock();
		return ;
	}

	LOG("0x33 tab_foreach");

	tab_foreach(p.tab, tab_delete, &req);

	db_unlock();
	write(sock, &req.cnt, 4);

	sy_log("\e[92m0x33\e[0m");
}
