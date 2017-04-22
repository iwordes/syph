/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 20:44:16 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/22 12:15:24 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#ifdef __BIG_ENDIAN__
# define EBYTE 0xff
#else
# define EBYTE 0x00
#endif

static void	init_header_(int fd)
{
	char	buff[4];

	buff[0] = EBYTE;
	buff[1] = 0x2a;
	*((uint16_t*)buff + 1) = 1;
	write(fd, buff, 4);
	*(uint32_t*)buff = 1;
	write(fd, buff, 4);
	write(fd, buff, 4);
}

int		db_init(/* ... */)
{
	if (ftruncate(/* ... */, 16 * 1024 * 1024) < 0)
		return (1);
	init_header_(/* ... */);
}
