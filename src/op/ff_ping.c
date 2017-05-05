/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ff_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 15:45:10 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/04 21:47:39 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

/*
** In the future, a server can lie about its endianness and simply convert to
** big endian for transmission if information about the server arch is a concern
*/

void	op_ff_ping(int sock)
{
	sy_log("\e[95m0xff\e[0m Ping");

	#ifdef __BIG_ENDIAN
	write(sock, "\xff", 1);
	#else
	write(sock, "", 1);
	#endif

	sy_log("\e[96m0xff\e[0m OK");
}
