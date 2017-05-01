/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   40_equ.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 15:48:10 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/30 16:58:57 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

bool	op_40_equ(t_field *meta, U8 *lhs, U8 *rhs)
{
	U64		i;

	i = meta->len * meta->size;
	while (i / 8)
	{
		if (*(U64*)(lhs + i) != *(U64*)(rhs + i))
			return (false);
		i -= 8;
	}
	while (i > 0)
	{
		if (*(lhs + i) != *(rhs + i))
			return (false);
		i -= 1;
	}
	return (true);
}
