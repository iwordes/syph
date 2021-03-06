/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 19:09:36 by iwordes           #+#    #+#             */
/*   Updated: 2017/06/22 11:33:03 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

static t_tab	g_init_head =
{
	~0,
	0,

	1,
	~0,

	TAB_BD_BLK,
	TAB_HD_BLK,

	{0},

	~0
};

static uint8_t	g_tsize[11][2] =
{
	{ 0x00, 1 },
	{ 0x01, 2 },
	{ 0x02, 4 },
	{ 0x03, 8 },
	{ 0x04, 1 },
	{ 0x05, 2 },
	{ 0x06, 4 },
	{ 0x07, 8 },
	{ 0x0d, 1 },

	{ 0x10, 4 },
	{ 0x11, 8 }
};

#define SCH ((t_field*)(tab + 1))[i]

static bool		tab__init(int sock, t_tab *tab, t_req21 *req)
{
	uint8_t		f;
	uint8_t		i;

	*tab = g_init_head;
	tab->id = DBH->next_id;
	tab->schema_len = req->schema_len;
	memcpy(tab->label, req->label, 32);
	if (!sy_read(sock, tab + 1, sizeof(t_field) * req->schema_len))
		return (false);
	i = ~0;
	tab->ent_size = 0;
	while (++i < req->schema_len)
	{
		f = ~0;
		while (++f < sizeof(g_tsize) / 2)
			if (g_tsize[f][0] == SCH.type)
			{
				SCH.size = g_tsize[f][1];
				tab->ent_size += SCH.size * SCH.len;
				break ;
			}
		if (f == sizeof(g_tsize) / 2)
			return (false);
	}
	return (true);
}

static void		end_(int sock, uint32_t res)
{
	LOG((res) ? "\e[92m0x21\e[0m" : "\e[91m0x21\e[0m");
	write(sock, &res, 4);
	db_unlock();
}

#define END(R) { end_(sock, R); return ; }

#define TAB_INDEX ((U32(*)[2])(DBH + 1))

/*
** 0x21
** 1. Lock the database for writing.
** 2. Attempt to read 34 bytes into our struct.
** 3. Fail if we've been given a zero-length schema.
** 4. If we already have a table with this label, return its ID.
** 5. Attempt to grow our database to fit a new table.
** 6. Get the block at the head of our new table.
** 7. Initialize the new table.
** 8. Create a new entry in our table index for this new table.
** 9. Cleanup, and unlock the database.
*/

void			op_21_create(int sock)
{
	t_tab		*tab;
	t_req21		req;

	db_wlock();
	LOG("\e[95m0x21\e[0m Create");
	if (!sy_read(sock, &req, 34))
		END(0);
	if (req.schema_len == 0)
		END(0);
	if ((tab = tab_by_label(req.label)) != NULL)
		END(tab->id);
	if (!db_grow(DB_BLK, TAB_BLK))
		END(0);
	tab = db_blk(DBH->next_off);
	if (!tab__init(sock, tab, &req))
		END(0);
	TAB_INDEX[DBH->next_id - 1][0] = DBH->next_id;
	TAB_INDEX[DBH->next_id - 1][1] = DBH->next_off;
	DBH->next_id += 1;
	DBH->next_off += TAB_BLK;
	DBH->tab_cnt += 1;
	end_(sock, tab->id);
}
