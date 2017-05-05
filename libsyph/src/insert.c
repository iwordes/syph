/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 16:39:21 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/05 13:09:25 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libsyph.h>

static void	pls_send(int sock, const t_sytab *tab, uint32_t cnt, void *data)
{
	uint8_t		id;

	write(sock, "\x30", 1);
	write(sock, &tab->id, 4);
	write(sock, &cnt, 4);
	write(sock, &tab->schema_len, 1);
	id = ~0;
	while (++id < tab->schema_len)
		write(sock, &id, 1);
	write(sock, data, cnt * tab->ent_size);
}

bool		sy_insert(const t_sytab *tab, uint32_t cnt, void *data)
{
	int			sock;
	int			r;

	if ((sock = sy__connit(tab->db)) < 0)
		return (false);
	pls_send(sock, tab, cnt, data);
	r = sy__read(sock, &cnt, 4);
	close(sock);
	return (r == 4);
}
