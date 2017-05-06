/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:48:14 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/05 18:57:37 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libsyph.h>

static uint8_t	g_sytype[][2] =
{
	{ SYT_U8, 1 },
	{ SYT_U16, 2 },
	{ SYT_U32, 4 },
	{ SYT_U64, 8 },
	{ SYT_I8, 1 },
	{ SYT_I16, 2 },
	{ SYT_I32, 4 },
	{ SYT_I64, 8 },
	{ SYT_UTF8, 1 },

	{ SYT_F32, 4 },
	{ SYT_F64, 8 },
};

#define F (tab->schema[i])

static bool		local_loop(t_sytab *tab)
{
	uint32_t	i;
	uint32_t	f;

	i = ~0;
	tab->ent_size = 0;
	while (++i < tab->schema_len)
	{
		f = ~0;
		while (++f < sizeof(g_sytype) / 2)
			if (g_sytype[f][0] == F.type)
			{
				F.size = g_sytype[f][1];
				break ;
			}
		if (f == sizeof(g_sytype) / 2)
			return (false);
		tab->ent_size += F.len * F.size;
	}
	return (true);
}

bool			sy_create(t_sytab *tab)
{
	int			sock;
	int			r;

	sock = sy__connit(tab->db);
	write(sock, "\x21", 1);
	write(sock, tab->label, 33);
	write(sock, &tab->schema_len, 1);
	write(sock, tab->schema, tab->schema_len * sizeof(t_syfield));
	r = sy__read(sock, &tab->id, 4);
	close(sock);
	return (r == 4 && tab->id != 0 && local_loop(tab));
}
