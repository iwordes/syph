/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_40_equ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 15:48:10 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/05 20:13:44 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

bool	op_40_equ(t_field *meta, U8 *lhs, U8 *rhs)
{
	if (meta->type == SYT_UTF8)
		return (strncmp((char*)lhs, (char*)rhs, meta->len) == 0);
	return (memcmp(lhs, rhs, meta->len * meta->size) == 0);
}
