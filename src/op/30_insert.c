/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 16:44:11 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/04 23:55:50 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define END(R) { end_(sock, R); return ; }

static void	end_(int sock, uint32_t res)
{
	if (res == 0)
		sy_log("\e[91m0x30\e[0m");
	else
		sy_log("\e[92m0x30\e[0m");
	write(sock, &res, 4);
	db_unlock();
}

#define F (req->field[f])
#define ENT_FIELD (ent + tab_foff(tab, F))
#define FIELD_SIZ (tab_field(tab, F)->size * tab_field(tab, F)->len)

static bool	ins1(t_tab *tab, t_req30 *req, int sock, uint32_t i)
{
	uint8_t		*ent;
	uint8_t		f;

	f = ~0;
	ent = tab_ent(tab, ~0);
	while (++f < req->field_len)
		if (!sy_read(sock, ENT_FIELD, FIELD_SIZ))
		{
			ent -= i * tab->ent_size;
			bzero(ent, (i + 1) * tab->ent_size);
			tab->len -= i;
			return (false);
		}
	*(U32*)ent = tab->next_id++;
	tab->len += 1;
	return (true);
}

static bool	chk_cost(t_tab *tab, t_req30 *req)
{
	uint32_t	at;

	if ((tab->len + 1 + req->limit) * tab->ent_size > tab->bd_blk * 4096)
	{
		at = ((void*)tab - (void*)DB.map) / 4096;
		if (!db_grow(at, tab->bd_blk))
			return (false);
		sy_log("ok yus");

		tab->bd_blk *= 2;
		sy_log("what");
	}
	sy_log("and return?");
	return (true);
}

void		op_30_insert(int sock)
{
	t_tab		*tab;
	t_req30		req;
	uint32_t	i;

	sy_log("\e[95m0x30\e[0m Insert");

	sy_read(sock, &req, 9);
	sy_read(sock, &req.field, req.field_len);

	db_wlock();

	if ((tab = table(req.tid)) == NULL)
		END(0);

	sy_log("chk_cost");

	if (!chk_cost(tab, &req))
		END(0);

	sy_log("ins1");

	for (i = 0; i < req.limit; i++)
		if (!ins1(tab, &req, sock, i))
			break ;

	END(req.limit);
}
