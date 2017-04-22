/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 20:44:16 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/22 14:43:04 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#ifdef __BIG_ENDIAN__
# define HEAD "\xff\x2a""\0\1""\0\0\0\1""\0\0\0\1"
#else
# define HEAD "\x00\x2a""\1\0""\1\0\0\0""\1\0\0\0"
#endif

int		db_init(const char *path)
{
	if ((fd = open(path, O_WRONLY, O_CREAT | O_EXCL | O_EXLOCK)) < 0)
		return (1);
	if (ftruncate(fd, 16 * 1024 * 1024) < 0)
	{
		close(fd);
		return (2);
	}
	if (write(fd, HEAD, 12) <= 0)
	{
		close(fd);
		return (3);
	}
	return (0);
}
