/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   by_label.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 17:38:03 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/04 23:54:57 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define TAB_INDEX ((U32(*)[2])(DBH + 1))
#define TAB_OFFSET TAB_INDEX[i][1]
#define TABLE ((char*)DBH + TAB_OFFSET * 4096)

t_tab	*tab_by_label(U8 label[33])
{
	U32		i;

	i = ~0;
	while (++i < DBH->tab_cnt)
	{
		sy_log(TABLE + 22);
		if (strncmp(TABLE + 22, (char*)label, 32) == 0)
			return ((t_tab*)TABLE);
	}
	return (NULL);
}
