/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:15:24 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/02 15:27:19 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

/*
** TODO: Handle comparisons
*/

void	tab_match(t_tab *tab, U8 *ent, t_tabmat *tm)
{
	U8		i;

	i = ~0;
	while (++i < tm->req.cmp_len)
		if (!tm->req.cmp[i](/* ... */))
			return ;
	tm->cnt += 1;
}
