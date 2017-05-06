/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:46:30 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/05 20:00:03 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libsyph.h>

static void		ip_pls(t_syph *sy)
{
	char	*serv;

	serv = sy->serv;
	((uint8_t*)&sy->ip)[0] = atoi(serv);
	while (*serv && *serv != '.')
		serv++;
	if (*serv)
		serv++;
	((uint8_t*)&sy->ip)[1] = atoi(serv);
	while (*serv && *serv != '.')
		serv++;
	if (*serv)
		serv++;
	((uint8_t*)&sy->ip)[2] = atoi(serv);
	while (*serv && *serv != '.')
		serv++;
	if (*serv)
		serv++;
	((uint8_t*)&sy->ip)[3] = atoi(serv);
}

static void		port_pls(t_syph *sy)
{
	char	*serv;

	serv = sy->serv;
	while (*serv && *serv != ':')
		serv++;
	if (*serv)
		serv++;
	sy->port = atoi(serv);
}

bool			sy_connect(t_syph *syph)
{
	int			sock;

	if (syph->serv != NULL)
	{
		ip_pls(syph);
		port_pls(syph);
	}
	if ((sock = sy__connit(syph)) < 0)
		return (false);
	write(sock, "\xff", 1);
	read(sock, &syph->be, 1);
	syph->be = !!syph->be;
	close(sock);
	return (true);
}
