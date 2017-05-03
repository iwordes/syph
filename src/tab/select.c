/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:23:44 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/03 13:34:29 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define C ts->req.cmp
#define F ts->req.field

#define CMP1 (tab_field(tab, C[i].id))
#define CMP2 (ent + tab_foff(tab, C[i].id))

#define CSIZE (tab_field(tab, C[i].id)->len * tab_field(tab, C[i].id)->size)

#define SIZE (tab_field(tab, F[i])->len * tab_field(tab, F[i])->size)

void	tab_select(t_tab *tab, U8 *ent, t_tabsel *ts)
{
	U8		i;

	if (ts.i == ts.req.limit)
		return ;

	// Filtration
	i = ~0;
	val = ts->req.cmp_val;
	while (++i < ts->req.cmp_len)
	{
		if (!ts->cmp[i](CMP1, CMP2, val))
			return ;
		val += CSIZE;
	}

	// Selection
	i = ~0;
	while (++i < ts->req.field_len)
		write(ts->sock, tab + tab_foff(tab, F[i]), SIZE);

	ts.i += 1;
}
