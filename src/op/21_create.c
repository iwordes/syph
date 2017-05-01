/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 19:09:36 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/30 14:16:19 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define MWRITE(T, V) *(T*)(g_mn.map + i) = (V); i += sizeof(T)

int		tab_create(const U8 label[33], U8 schema_len, t_field *schema)
{
	t_req21	req;
	U8		*tab;
	U64		i;

	sy_read(sock, &req, sizeof(req));
	// 1. Check for existing table of same label.
	if (/* tab_exists(req.label) */)
		return (1);

	if (db_grow(g_mn.db.head->next_off + 1 + BD_BLK_DFL))
		return (2);
	i = 0;
	tab = (U8*)(map + g_mn.db.head->next_off * 4096);
	MWRITE(U32, g_mn.db.head->next_id);
	MWRITE(U32, 0);
	MWRITE(U32, 1);
	MWRITE(U32, BD_BLK_DFL);
	MWRITE(U16, 1);
	memcpy(tab + i, req.label, 32);
	i += 33;
	MWRITE(U8, req.schema_len + 1);
	MWRITE(U8, TYPE_U32);
	MWRITE(U8, 0);
	MWRITE(U16, 4);
	MWRITE(U32, 1);
	sy_read(sock, tab + i, sizeof(t_field) * req.schema_len);
	g_mn.db.head->next_id += 1;
	g_mn.db.head->next_off += 1 + BD_BLK_DFL;
	return (0);
}
