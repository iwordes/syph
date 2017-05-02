/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 15:07:52 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/02 15:27:08 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

/*
** TODO: Handle comparisons
*/

void	tab_delete(t_tab *tab, U8 *ent, t_tabdel *td)
{
	U8		i;

	i = ~0;
	while (++i < td->req.cmp_len)
		if (!td->req.cmp[i](/* ... */))
			return ;
	bzero(ent, tab->entry_size);
}
