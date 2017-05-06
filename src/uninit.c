/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uninit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 10:33:19 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/05 17:42:51 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

void	uninit(int z)
{
	sy_log("Destroying thread pool...");
	tp_destroy(g_mn.tp);
	;
	sy_log("Shutting down server...");
	shutdown(g_mn.sock, SHUT_RDWR);
	close(g_mn.sock);
	;
	sy_log("Unloading database...");
	db_unload();
	;
	sy_log("\e[1;92mDone.\e[0m");
	pthread_mutex_destroy(&g_mn.llock);
	close(g_mn.log);
	exit(0);
	(void)z;
}
