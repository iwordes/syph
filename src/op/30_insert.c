/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 16:44:11 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/05 14:59:31 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define END(R) { end_(sock, R); return ; }

static void		end_(int sock, uint32_t res)
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

static bool		ins1(t_tab *tab, t_req30 *req, int sock, uint32_t i)
{
	uint8_t		*ent;
	uint8_t		f;

	printf("ent_size: %u\n", tab->ent_size);

	f = ~0;
	ent = tab_ent(tab, ~0);

	static uint8_t*p = NULL;
	printf("%p\n", (void*)(ent - p));
	p = ent;

	while (++f < req->field_len)
	{
		if (!sy_read(sock, ENT_FIELD, FIELD_SIZ))
		{
			ERROR("Could not read into entry!");
			lprintf("             errno %d: %s\n", errno, strerror(errno));
			lprintf("             ent -= %d * %u;\n", i, tab->ent_size);
			ent -= i * tab->ent_size;
			lprintf("             bzero(ent, %u);\n", (i + 1) * tab->ent_size);
			bzero(ent, (i + 1) * tab->ent_size);
			lprintf("             tab->len -= %d;\n", i);
			tab->len -= i;
			LOG("\e[91mins1\e[0m");
			return (false);
		}
	}
	*(U32*)ent = tab->next_id++;
	tab->len += 1;
	printf("%.2u\t%.11s\t%.65s\n", *(U32*)ent, (I8*)(ent + 4), (I8*)(ent + 15));
	return (true);
}

#define NEED_BLK ((tab->len + 1 + req->limit) * tab->ent_size)
#define HAVE_BLK (tab->bd_blk * 4096)

#define OFF_BLK (((void*)tab - (void*)DBH) / 4096)
#define GROW_AT OFF_BLK + tab->hd_blk + tab->bd_blk

static t_tab	*chk_cost(t_req30 *req)
{
	t_tab		*tab;

	if ((tab = table(req->tid)) == NULL)
		return (NULL);
	if (NEED_BLK > HAVE_BLK)
	{
		if (!db_grow(GROW_AT, tab->bd_blk))
			return (NULL);

		if ((tab = table(req->tid)) == NULL)
			FATAL("Somehow lost the table just grown!");

		DBH->next_off += tab->bd_blk;
		tab->bd_blk *= 2;
	}
	return (tab);
}

void			op_30_insert(int sock)
{
	t_tab		*tab;
	t_req30		req;
	uint32_t	i;

	LOG("\e[95m0x30\e[0m Insert");

	sy_read(sock, &req, 9);
	sy_read(sock, req.field, req.field_len);

	db_wlock();

	if ((tab = chk_cost(&req)) == NULL)
		END(0);

	for (i = 0; i < req.limit; i++)
		if (!ins1(tab, &req, sock, i))
			break ;

	END(req.limit);
}
