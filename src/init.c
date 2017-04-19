/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 10:33:31 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/19 10:43:05 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

t_arg	g_arg[] = {
	{ "daemon", arg_daemon, 0 },
	{ "home", arg_home, 1 },
	{ "v", arg_verbose, 0 },
	{ NULL, NULL, 0 }
};

void	init(int *argc, char ***argv)
{
	arg_parse(argc, argv, g_arg);
	if (g_mn.v)
		printf("\e[96mFlags\e[0m\n  daemon: %d\n  home: %s\n  v: %d\n",
				g_mn.daemon, g_mn.home, g_mn.v);
	// ...
}
