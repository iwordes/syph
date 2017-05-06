/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_connit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:57:03 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/05 19:45:11 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libsyph.h>

int		sy__connit(t_syph *db)
{
	int		sock;
	t_sysa	sa;

	sa.sin_family = AF_INET;
	sa.sin_port = htons(db->port);
	sa.sin_addr.s_addr = db->ip;
	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		return (-1);
	if (connect(sock, (void*)&sa, sizeof(sa)) < 0)
	{
		close(sock);
		return (-2);
	}
	return (sock);
}
