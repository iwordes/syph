/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:23:44 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/02 15:26:52 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

/*
** TODO
** 1. Handle comparisons
** 2. Find field location and size, write to socket
*/

void	tab_select(t_tab *tab, U8 *ent, t_tabsel *ts)
{
	U8		i;

	i = ~0;
	while (++i < ts->req.cmp_len)
		if (!ts->cmp[i](/* ... */))
			return ;
	i = ~0;
	while (++j < ts->req.field_len)
		write(ts->sock, /* data */, /* len */);
}
