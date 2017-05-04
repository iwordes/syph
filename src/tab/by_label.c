/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   by_label.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 17:38:03 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/04 12:29:42 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define TAB_OFFSET (((U32(*)[2])(DB.head + 1))[i][1] * 4096)

t_tab	*tab_by_label(U8 label[33])
{
	U32		i;

	i = ~0;
	while (++i < DBH->tab_cnt)
		if (strncmp(DB.map + TAB_OFFSET + 22, label, 32) == 0)
			return ((t_tab*)(DB.map + TAB_OFFSET));
	return (NULL);
}
