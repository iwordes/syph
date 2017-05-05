/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foff.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 11:09:46 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/05 11:51:23 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define F ((t_field*)(&tab->schema_len + 1))
#define SIZE (F[i].size * F[i].len)

off_t	tab_foff(t_tab *tab, U8 id)
{
	off_t	off;
	U8		i;

	printf("\e[95mfoff\e[0m(%s, %hhu)\n", tab->label, id);
	printf("schema[%hhu]\n", tab->schema_len);

	i = ~0;
	off = 0;
	id %= tab->schema_len;
	while (++i < id)
	{
		printf("    + %u\n", SIZE);
		off += SIZE;
	}

	printf("\e[92mfoff\e[0m -> %lld\n", off);
	return (off);
}
