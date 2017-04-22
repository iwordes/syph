/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 13:40:07 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/22 16:48:29 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define TYPE &(tbl_hd(&g_mn.db, tid)->field)[fid]

bool	tbl_fcmp(t_db *db, uint32_t tid, uint8_t fid, t_box val)
{
	uint8_t	type;

	type = g_mn.db
}
