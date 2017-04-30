/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 19:39:20 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/29 20:23:33 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

void	init_sock(void)
{
	struct sockaddr_in	sa;

	g_mn.sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (g_mn.sock < 0)
		exit(DBE_SOPEN);
	sa.sin_port = g_mn.port;
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = INADDR_ANY;
	if (bind(g_mn.sock, (void*)&sa, sizeof(sa)) < 0)
		exit(DBE_SBIND);
	if (listen(sock, 128) < 0)
		exit(DBE_SLIST);
}
