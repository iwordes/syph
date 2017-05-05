/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <kdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 19:09:31 by kdavis            #+#    #+#             */
/*   Updated: 2017/05/05 13:34:50 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libsyph.h>

static void	pls_send(int sock, t_sysel *sel)
{
	uint8_t		id;

	write(sock, "\x31", 1);
	write(sock, &sel->tab->id, 4);
	write(sock, &sel->limit, 4);
	write(sock, &sel->tab->schema_len, 1);
	id = ~0;
	while (++id < sel->tab->schema_len)
		write(sock, &id, 1);
	write(sock, &sel->cmp.len, 1);
	write(sock, &sel->cmp.cmp, sel->cmp.len * 2);
	write(sock, &sel->cmp.data, sel->cmp.data_len);
}

#define LEN (sel->tab->ent_size * sel->cnt)

static bool	pls_recv(int sock, t_sysel *sel)
{
	if (sy__read(sock, &sel->cnt, 4) != 4)
		return (false);
	return (sy__read(sock, sel->data, LEN) >= 0);
}

bool		sy_select(t_sysel *sel)
{
	int		sock;
	bool	ok;

	sock = sy__connit(sel->tab->db);
	if (sock < 0)
		return (false);
	pls_send(sock, sel);
	ok = pls_recv(sock, sel);
	close(sock);
	return (ok);
}
