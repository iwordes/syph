/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 19:09:36 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/04 21:47:26 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

static t_tab	g_init_head =
{
	~0,
	0,

	1,
	~0,

	TAB_HD_BLK,
	TAB_BD_BLK,

	{0},

	~0
};

static void		tab__init(int sock, t_tab *tab, t_req21 *req)
{
	*tab = g_init_head;
	tab->id = DBH->next_id;
	tab->schema_len = req->schema_len;
	memcpy(tab->label, req->label, 32);
	sy_read(sock, tab + 1, sizeof(t_field) * req->schema_len);
}

static void		end_(int sock, uint32_t res)
{
	write(sock, &res, 4);
	db_unlock();
}

#define END(R) { end_(sock, R); return ; }

#define TAB_INDEX ((U32(*)[2])(DBH + 1))

void			op_21_create(int sock)
{
	t_tab		*tab;
	t_req21		req;

	sy_read(sock, &req, sizeof(req));
	db_wlock();

	sy_log("\e[95m0x21\e[0m Create");
	sy_log((char*)req.label);

	if ((tab = tab_by_label(req.label)) != NULL)
		END(tab->id);

	if (!db_grow(DB_BLK, TAB_BLK))
		END(0);

	tab = db_blk(DBH->next_off);

	tab__init(sock, tab, &req);

	TAB_INDEX[DBH->next_off - 1][0] = DBH->next_id;
	TAB_INDEX[DBH->next_off - 1][1] = DBH->next_off;
	DBH->next_id += 1;
	DBH->next_off += TAB_BLK;
	DBH->tab_cnt += 1;

	end_(sock, tab->id);

	sy_log("\e[96m0x21\e[0m OK");
}
