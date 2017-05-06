/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   40_equ.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 15:48:10 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/04 14:50:25 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

bool	op_40_equ(t_field *meta, U8 *lhs, U8 *rhs)
{
	if (meta->type == SYT_UTF8)
		return (strcmp((char*)lhs, (char*)rhs) == 0);
	return (memcmp(lhs, rhs, meta->len * meta->size));
}
