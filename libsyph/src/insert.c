/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 16:39:21 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/03 16:56:25 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libsyph.h>

bool	sy_insert(const t_sytab *tab, uint32_t len, void *data)
{
	int			sock;
	uint32_t	tid;
	uint8_t		i;
	int			r;

	tid = (tab->db->be) ? htonl(tab->id) : tab->id;
	sock = sy__connit(tab->db);
	write(sock, "\x30", 1);
	write(sock, &tid, 4);
	write(sock, &len, 4);

	i = ~0;
	write(sock, &tab->schema_len, 1);
	while (++i < tab->schema_len)
		write(sock, &i, 1);

	write(sock, data, len * tab->ent_size);
	r = sy__read(sock, &len, 4);
	len = ntohl(len);
	close(sock);
	return (r == 4 && len != 0);
}
