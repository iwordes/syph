/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 19:09:36 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/30 18:20:03 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define THEAD t_tab_head

static THEAD	g_init_head =
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

static int		panic(int n)
{
	db_unlock();
	return (n);
}

# define DHEAD g_mn.db.head

int				op_21_create(const U8 label[33], U8 schema_len, t_field *schema)
{
	t_tab_head	*tab;
	t_req21		req;

	sy_read(sock, &req, sizeof(req));
	db_wlock();
	if (tab_by_label(req.label) != NULL)
		PANIC(1);
	if (db_grow(DHEAD->next_off + 1 + BD_BLK_DFL))
		PANIC(2);
	tab = (t_tab_head*)(map + DHEAD->next_off * 4096);
	*tab = g_init_head;
	memcpy(tab->label, req.label, 32);
	tab->id = DHEAD->next_id;
	tab->schema_len = req.schema_len;
	sy_read(sock, tab + 1, sizeof(t_field) * req.schema_len);
	DHEAD->next_id += 1;
	DHEAD->next_off += TAB_HD_BLK + TAB_BD_BLK;
	db_unlock();
	return (0);
}
