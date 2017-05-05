/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:46:30 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/04 21:32:19 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libsyph.h>

bool	sy_connect(t_syph *syph)
{
	int			sock;

	if ((sock = sy__connit(syph)) < 0)
		return (false);
	write(sock, "\xff", 1);
	read(sock, &syph->be, 1);
	syph->be = !!syph->be;
	close(sock);
	return (true);
}
