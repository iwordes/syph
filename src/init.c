/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 10:33:31 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/03 19:25:13 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

static void	init_init(int *argc, char ***argv)
{
	if (*argc > 1 && chdir((*argv)[1]) < 0)
		exit(DBE_CHDIR);
	g_mn.log = open("syph.log", O_RDWR | O_CREAT | O_APPEND, 0600);
	if (g_mn.log < 0)
		exit(DBE_O_LOG);
}

void	init(int *argc, char ***argv)
{
	init_init(argc, argv);
	sy_log("Starting...");
	init_config();
	init_thread();
	init_socket();
	init_signal();
	sy_log("Ready.");
}
