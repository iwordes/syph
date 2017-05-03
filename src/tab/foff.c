/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foff.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 11:09:46 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/03 11:14:57 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define F tab->schema
#define SIZE (F[i].size * F[i].len)

off_t	tab_foff(t_tab *tab, U8 id)
{
	off_t	off;
	U8		i;

	i = ~0;
	id %= tab->schema_len;
	while (++i < id)
		off += SIZE;
	return (off);
}
