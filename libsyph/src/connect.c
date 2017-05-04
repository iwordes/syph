/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:46:30 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/03 17:49:02 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libsyph.h>

t_syph		sy_connect(uint8_t ip[4], uint16_t port)
{
	t_syph		syph;
	int			sock;

	bzero(&syph, sizeof(syph));
	syph.port = port;
	syph.ip[0] = ip[0];
	syph.ip[1] = ip[1];
	syph.ip[2] = ip[2];
	syph.ip[3] = ip[3];
	sock = sy__connit(&syph);
	write(sock, "\xff", 1);
	read(sock, &syph.be, 1);
	syph.be = !!syph.be;
	close(sock);
	return (syph);
}
