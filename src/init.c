/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 10:33:31 by iwordes           #+#    #+#             */
/*   Updated: 2017/06/22 11:21:48 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

static void	init_init(int *argc, char ***argv)
{
	if (*argc > 1)
		mkdir((*argv)[1], 0700);
	if (*argc > 1 && chdir((*argv)[1]) < 0)
		exit(DBE_CHDIR);
	g_mn.log = open("syph.log", O_RDWR | O_CREAT | O_APPEND, 0600);
	if (g_mn.log < 0)
		exit(DBE_O_LOG);
	if (pthread_mutex_init(&g_mn.llock, NULL))
		exit(DBE_LLOCK);
}

/*
** 1. Change directory and initate logging.
** 2. Load the database.
** 3. Create the thread pool.
** 4. Create the socket to listen on.
** 5. Handle signals.
*/

void		init(int *argc, char ***argv)
{
	init_init(argc, argv);
	LOG("\e[1mStart.\e[0m");
	init_config();
	init_thread();
	init_socket();
	init_signal();
	LOG("\e[1;92mReady.\e[0m");
}

/*
** dprintf(g_mn.log, "g_mn.db.head = {\n");
** dprintf(g_mn.log, "    ebyte    = %hhu\n", DBH->ebyte);
** dprintf(g_mn.log, "    x21      = %hhu\n", DBH->x2a);
** dprintf(g_mn.log, "    hd_blk   = %hu\n", DBH->hd_blk);
** dprintf(g_mn.log, "    bd_blk   = %u\n", DBH->bd_blk);
** dprintf(g_mn.log, "    next_id  = %u\n", DBH->next_id);
** dprintf(g_mn.log, "    next_off = %u\n", DBH->next_off);
** dprintf(g_mn.log, "    tab_cnt  = %u\n", DBH->tab_cnt);
** dprintf(g_mn.log, "}\n");
*/
