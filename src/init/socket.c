/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 19:39:20 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/04 18:46:14 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

/*
** TODO: Custom port
*/

void	init_socket(void)
{
	struct sockaddr_in	sa;

	g_mn.port = 4243;
	sy_log("Initializing socket...");
	dprintf(g_mn.log, "             Port: %hd\n", g_mn.port);
	g_mn.sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (g_mn.sock < 0)
		FATAL("Could not open socket!");
	sa.sin_port = htons(g_mn.port);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = INADDR_ANY;
	if (bind(g_mn.sock, (void*)&sa, sizeof(sa)) < 0)
		FATAL("Could not bind socket!");
	if (listen(g_mn.sock, 128) < 0)
		FATAL("Could not listen on socket!");
}
