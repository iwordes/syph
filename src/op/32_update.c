/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   32_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 15:38:54 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/04 22:21:08 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define E1 { db_unlock(); return ; }
#define E2 { db_unlock(); free(req.cmp_val); return ; }

void	op_32_update(int sock)
{
	t_req32		req;
	t_getpair	p;

	sy_log("\e[95m0x32\e[0m Update");

	bzero(&req, sizeof(req));
	sy_read(sock, &req, 6);

	db_wlock();

	p.sock = sock;
	if ((p.tab = table(req.tid)) == NULL)
		E1;
	if (sy_getpair(p, req.cmp_len, req.cmp, &req.cmp_val))
		E1;
	if (sy_getpair(p, req.asn_len, req.asn, &req.asn_val))
		E2;

	tab_foreach(p.tab, tab_update, &req);

	db_unlock();
	write(sock, &req.cnt, 4);
	free(req.cmp_val);
	free(req.asn_val);

	sy_log("\e[92m0x32\e[0m");
}
