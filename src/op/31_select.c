/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <kdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 12:13:51 by kdavis            #+#    #+#             */
/*   Updated: 2017/05/05 13:38:59 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

void	op_31_select(int sock)
{
	t_tab		*tab;
	t_req31		req;
	t_getpair	p;

	sy_log("\e[95m0x31\e[0m Select");

	bzero(&req, sizeof(req));

	sy_read(sock, &req, 9);
	sy_read(sock, req.field, req.field_len);

	db_rlock();
	tab = table(req.tid);

	p.tab = tab;
	p.sock = sock;
	if (sy_getpair(p, req.cmp_len, req.cmp, &req.cmp_val) != 0)
	{
		LOG("\e[91m0x31\e[0m");
		db_unlock();
		return ;
	}

	tab_foreach(tab, tab_match, &req);

	lprintf("[%ld] 0x31 %u Results\n", time(NULL), req.cnt);

	write(sock, &req.cnt, 4);
	req.cnt = 0;

	req.sock = sock;
	tab_foreach(tab, tab_select, &req);
	db_unlock();

	free(req.cmp_val);

	sy_log("\e[92m0x31\e[0m");
}
