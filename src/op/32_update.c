/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   32_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 15:38:54 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/04 14:45:41 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>



#define REQ tu.req

#define E1 { db_unlock(); return ; }
#define E2 { db_unlock(); free(REQ.cmp_val); return ; }

void	op_32_update(int sock)
{
	t_tabupd	tu;
	t_getpair	p;

	bzero(&tu, sizeof(tu));
	sy_read(sock, &REQ, 6);
	db_wlock();
	p.sock = sock;
	if ((p.tab = table(REQ.tid)) == NULL)
		E1;
	if (sy_getpair(p, REQ.cmp_len, REQ.cmp, &REQ.cmp_val))
		E1;
	if (sy_getpair(p, REQ.asn_len, REQ.asn, &REQ.asn_val))
		E2;
	tab_foreach(p.tab, tab_update, &tu);
	db_unlock();
	write(sock, &tu.cnt, 4);
	free(REQ.cmp_val);
	free(REQ.asn_val);
}
