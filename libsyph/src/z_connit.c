/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_connit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:57:03 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/04 20:27:54 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libsyph.h>

#define ADDR ((uint8_t*)(&sa.sin_addr.s_addr))

int		sy__connit(t_syph *db)
{
	int		sock;
	t_sysa	sa;

	sa.sin_family = AF_INET;
	sa.sin_port = htons(db->port);
	ADDR[0] = db->ip[0];
	ADDR[1] = db->ip[1];
	ADDR[2] = db->ip[2];
	ADDR[3] = db->ip[3];
	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		return (-1);
	if (connect(sock, (void*)&sa, sizeof(sa)) < 0)
	{
		close(sock);
		return (-2);
	}
	return (sock);
}
