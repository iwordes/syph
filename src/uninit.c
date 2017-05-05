/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uninit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 10:33:19 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/04 18:43:45 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

void	uninit(int z)
{
	sy_log("Shutting down...");
	tp_destroy(g_mn.tp);
	close(g_mn.sock);
	close(g_mn.log);
	db_unload();
	(void)z;
}
