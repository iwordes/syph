/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreach.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 15:09:18 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/02 15:21:42 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define I (i * tab->entry_size)
#define FT void (*)(t_tab*, U8*, void*)

void	tab_foreach(U32 tid, void *fn, void *ctx)
{
	t_tab	*tab;
	U8		*bd;
	U32		i;

	if ((tab = table(tid)) == NULL)
		return ;
	i = ~0;
	bd = ((U8*)tab) + tab->hd_blk * 4096;
	while (++i < tab->len)
		if (*(U32*)(bd + I) != 0)
			((FT)fn)(tab, bd + I, ctx);
}
