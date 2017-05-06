/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   33_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 15:01:40 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/05 18:04:42 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define END { LOG("\e[91m0x33\e[0m"); db_unlock(); return ; }

void	op_33_delete(int sock)
{
	t_req33		req;
	t_getpair	p;

	LOG("\e[95m0x33\e[0m Delete");
	bzero(&req, sizeof(req));
	db_wlock();
	if (!sy_read(sock, &req, 9))
		END;
	p.tab = table(req.tid);
	p.sock = sock;
	if (!sy_getpair(p, req.cmp_len, req.cmp, &req.cmp_val))
		END;
	LOG("0x33 Deleting...");
	tab_foreach(p.tab, tab_delete, &req);
	db_unlock();
	write(sock, &req.cnt, 4);
	lprintf("[%.8s] \e[92m0x33\e[0m %u deleted\n", sy_time(), req.cnt);
}
