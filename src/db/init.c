/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 20:44:16 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/20 21:54:15 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#ifdef __BIG_ENDIAN__
# define EBYTE 0xFF
#else
# define EBYTE 0x00
#endif

static void	init_header_(int fd)
{
	char	buff[4];

	// 1. Write endian byte 0x00/0xff
	buff[0] = EBYTE;
	buff[1] = 0x42;
	*(uint16_t)(*&buff + 2) = 1;
	write(fd, buff, 4);

	// 2. Go to end of block
	lseek(fd, 4095, SEEK_SET);

	// 3. Write 0x00 (grow file to at least 4096 bytes)
	write(fd, &(buff = 0x00), 1);
}

int		db_init(/* ... */)
{
	init_header_(/* ... */);

}
