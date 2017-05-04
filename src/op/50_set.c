/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   50_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 15:50:52 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/04 14:50:55 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

void	op_50_set(t_field *meta, U8 *field, U8 *data)
{
	if (meta->type == SYT_UTF8)
		memcpy(field, data + 4, *(U32*)data);
	memcpy(field, data, meta->size * meta->len);
}
