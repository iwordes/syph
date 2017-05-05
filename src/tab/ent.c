/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 13:27:39 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/05 15:08:49 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

/*
** Get an entry by id.
** 0: First entry
** ~0: Last entry
*/

uint8_t		*tab_ent(t_tab *tab, uint32_t id)
{
	uint8_t		*ent;
	uint32_t	i;


	printf("Users {\n");
	printf("    id: %u\n", tab->id);
	printf("    len: %u\n", tab->len);
	printf("    next_id: %u\n", tab->next_id);
	printf("    ent_size: %u\n", tab->ent_size);
	printf("    bd_blk: %u\n", tab->bd_blk);
	printf("    hd_blk: %hu\n", tab->hd_blk);
	printf("    label: '%s'\n", (char*)tab->label);
	printf("    schema_len: %hhu\n", tab->schema_len);
	printf("}\n");

	i = 0;
	ent = (U8*)tab + (tab->hd_blk * 4096);

	printf("tab -> body: %ld\n", (void*)ent - (void*)tab);

	if (id == 0)
		return (ent);
	if (id == ~0U)
		return (ent + tab->len * tab->ent_size);
	while (i < tab->len)
	{
		if (*(U32*)ent == id)
			break ;
		ent += tab->ent_size;
		i += 1;
	}
	return (ent);
}
