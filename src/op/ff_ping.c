/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ff_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 15:45:10 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/28 15:47:53 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

/*
** In the future, a server can lie about its endianness and simply convert to
** big endian for transmission if information about the server arch is a concern
*/

void	op_ff_ping(int sock)
{
	#ifdef __BIG_ENDIAN
	write(sock, "\xff", 1);
	#else
	write(sock, "", 1);
	#endif
}
