/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <kdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 12:13:51 by kdavis            #+#    #+#             */
/*   Updated: 2017/05/03 13:48:23 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

void	op_31_select(int sock)
{
	t_req31		req;
	t_tabsel	ts;
	t_getpair	p;

	bzero(&ts, sizeof(ts));
	bzero(&req, sizeof(req));
	sy_read(sock, &req, 11);
	ts.req = &req;
	db_rlock();
	tab = table(req.tid);

	p.tab = tab;
	p.sock = sock;
	if (sy_getpair(p, req.cmp_len, &req.cmp, &req.cmp_val))
	{
		db_unlock();
		return ;
	}

	tab_foreach(tab, tab_match, &ts);
	ts.cnt = MIN(ts.cnt, req.limit);
	write(sock, &ts.cnt, 4);

	tab_foreach(tab, tab_select, &ts);
	db_unlock();

	free(req.cmp_val);
}
