/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 16:39:21 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/04 21:26:31 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libsyph.h>

static void	pls_send(int sock, const t_sytab *tab, uint32_t len, void *data)
{
	write(sock, "\x30", 1);
	write(sock, &cnt, 4);
	write(sock, &tab->schema_len, 1);
	write(sock, tab->schema, tab->schema_len * sizeof(t_syfield));
	write(sock, data, cnt * tab->ent_size);
}

bool		sy_insert(const t_sytab *tab, uint32_t cnt, void *data)
{
	int			sock;
	uint8_t		i;
	int			r;

	if ((sock = sy__connit(tab->db)) < 0)
		return (false);
	pls_send(sock, tab, cnt, data);
	r = sy__read(sock, &cnt, 4);
	close(sock);
	return (r == 4);
}
