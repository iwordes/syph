/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:29:20 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/02 15:27:27 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

/*
** TODO: Handle comparisons
** TODO: Handle assignments
*/

void	tab_update(t_tab *tab, U8 *ent, t_tabupd *tu)
{
	U8		i;

	i = ~0;
	while (++i < tu->req.cmp_len)
		if (!tu->req.cmp[i](/* ... */))
			return ;
	i = ~0;
	while (++i < tu->req.assign_len)
		tu->req.assign[i](/* ... */);
}
