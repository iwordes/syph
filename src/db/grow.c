/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 10:57:31 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/03 20:10:52 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define DB g_mn.db
#define HEAD DB.head

#define HD_BLK HEAD->hd_blk
#define BD_BLK HEAD->bd_blk
#define BLOCKS ((HD_BLK + BD_BLK) * 4096)

static void	backup_(const char *path)
{
	char	path2[4096];

	bzero(path2, 4096);
	strcat(path2, path);
	strcat(path2, "~");
	remove(path2);
	link(path, path2);
	remove(path);
}

static bool	restore_(int fd)
{
	char	path2[4096];

	bzero(path2, 4096);
	strcat(path2, DB.name);
	strcat(path2, "~");
	remove(DB.name);
	link(path2, DB.name);
	remove(path2);
	close(fd);
	return (false);
}


bool	db_grow(uint32_t at, uint32_t skip)
{
	uint8_t	*tmp_map;
	int		tmp;

	// 1. Move DB to DB~
	backup_(DB.name);

	// 2. Create new DB
	if ((tmp = open(DB.name, O_RDWR | O_CREAT | O_EXCL | O_EXLOCK, 0600)) < 0)
		return (restore_(tmp));

	// 3. Copy old DB to new DB until offset
	if (write(tmp, DB.map, at * 4096) <= 0)
		return (restore_(tmp));

	// 4. Skip N blocks
	if (lseek(tmp, skip * 4096, SEEK_CUR) < 0)
		return (restore_(tmp));

	// 5. Copy rest of old DB to new DB
	if (write(tmp, DB.map + (at * 4096), (HD_BLK + BD_BLK - at) * 4096) <= 0)
		return (restore_(tmp));

	// 6. mmap() new DB
	tmp_map = mmap(NULL, BLOCKS + (skip * 4096), PROT_RW, MAP_SHARED, tmp, 0);
	if (tmp_map == NULL)
		return (restore_(tmp));

	// 7. Unload old DB
	munmap(DB.map, BLOCKS);
	close(DB.fd);

	// 8. Load new map
	DB.fd = tmp;
	DB.map = tmp_map;
	HEAD = (void*)DB.map;

	// 9. Increment blockcount
	BD_BLK += skip;

	return (true);
}
