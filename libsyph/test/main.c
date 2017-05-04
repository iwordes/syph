/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 17:23:57 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/03 17:30:27 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libsyph.h>

typedef struct	table
{
	uint32_t	id;
	uint8_t		user[8];
	uint8_t		pass[32];
}				table;

t_sytab			sytab =
{
	"Users",
	3,
	{
		{ SYT_U32, false, true, 4, 1 },
		{ SYT_U8, false, true, 1, 8 },
		{ SYT_U8, false, false, 1, 32 }
	},

	NULL,
	0,
	0
};

table			tabdata[5] =
{
	{ ~0, "user", "pass" },
	{ ~0, "iwordes", "pass" },
	{ ~0, "kdavis", "pass" },
	{ ~0, "kyork", "pass" },
	{ ~0, "smifsud", "pass" }
};

int		main()
{
	t_sysel	sel;
	table	tab;
	t_syph	db;
	table	*r;

	db = sy_connect({ 127, 0, 0, 1 }, 4243);
	sytab.db = &db;
	if (!sy_create(&sytab))
		return (1);
	if (!sy_insert(sytab, 5, tabdata))
		return (2);
	sel = sy_select(sytab, {1, { 0x50, 0 }, 4, "\1\0\0\0"});
	if (sel->cnt < 5)
		return (3);
	r = sel->data;
	for (int i = 0; i < 5; i++)
		printf("%.3d\t\"%8s\"\t\"%32s\"", r[i].id, r[i].user, r[i].pass);
	return (0);
}
