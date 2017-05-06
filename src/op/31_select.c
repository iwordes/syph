/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <kdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 12:13:51 by kdavis            #+#    #+#             */
/*   Updated: 2017/05/05 18:05:36 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define END { LOG("\e[91m0x31\e[0m"); db_unlock(); return ; }

void	op_31_select(int sock)
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
	tab = table(req.tid);
	p.tab = tab;
	p.sock = sock;
	if (!sy_getpair(p, req.cmp_len, req.cmp, &req.cmp_val))
		END;
	LOG("0x31 Selecting...");
	tab_foreach(tab, tab_match, &req);
	write(sock, &req.cnt, 4);
	req.cnt = 0;
	req.sock = sock;
	tab_foreach(tab, tab_select, &req);
	db_unlock();
	free(req.cmp_val);
	lprintf("[%.8s] \e[92m0x31\e[0m %u selected\n", sy_time(), req.cnt);
}
