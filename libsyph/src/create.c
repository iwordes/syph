/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:48:14 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/03 16:55:03 by iwordes          ###   ########.fr       */
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
	write(sock, tab, 34 + (tab->schema_len * sizeof(t_syfield)));
	r = sy__read(sock, &tab.tid, 4);
	close(sock);
	i = ~0;
	while (++i < tab->schema_len)
		tab->ent_len += tab->schema[i].len * tab->schema[i].size;
	return (r == 4 && tab.tid != 0);
}
