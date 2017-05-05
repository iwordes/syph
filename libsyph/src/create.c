/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:48:14 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/05 12:31:11 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libsyph.h>

bool		sy_create(t_sytab *tab)
{
	int			sock;
	int			r;
	uint32_t	i;

	sock = sy__connit(tab->db);
	write(sock, "\x21", 1);
	write(sock, tab->label, 33);
	write(sock, &tab->schema_len, 1);
	write(sock, tab->schema, tab->schema_len * sizeof(t_syfield));
	r = sy__read(sock, &tab->id, 4);
	close(sock);
	i = ~0;
	while (++i < tab->schema_len)
		tab->ent_size += tab->schema[i].len * tab->schema[i].size;
	return (r == 4 && tab->id != 0);
}
