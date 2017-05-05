/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <kdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 12:13:51 by kdavis            #+#    #+#             */
/*   Updated: 2017/05/04 21:47:07 by iwordes          ###   ########.fr       */
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

	sy_read(sock, &req, 11);

	db_rlock();
	tab = table(req.tid);

	p.tab = tab;
	p.sock = sock;
	if (sy_getpair(p, req.cmp_len, req.cmp, &req.cmp_val))
	{
		db_unlock();
		return ;
	}

	tab_foreach(tab, tab_match, &req);
	write(sock, &req.cnt, 4);
	req.cnt = 0;

	req.sock = sock;
	tab_foreach(tab, tab_select, &req);
	db_unlock();

	free(req.cmp_val);

	sy_log("\e[96m0x31\e[0m OK");
}
