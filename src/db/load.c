/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 12:32:16 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/03 20:17:24 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define MAP (mmap(NULL, DB.size, PROT_RW, MAP_SHARED, DB.fd, 0))
#define PANIC(N) return (panic(N))

static char	*g_emsg[] =
{
	"Failed to open database.",
	"Invalid database: Size is not a multiple of 4096.",
	"Failed to map database into memory.",
	"Invalid database: Endian byte mismatch.",
	"Invalid database: Missing 0x2a at offset 1.",
	"Failed to allocate space for rwlock."
};

static int	panic(int n)
{
	if (n > 6)
		pthread_rwlock_destroy(&DB.lock);
	if (n > 3)
		munmap(DB.map, (DBH->hd_blk + DBH->bd_blk) * 4096);
	if (n > 1)
		close(DB.fd);
	ERROR(g_emsg[n - 1]);
	return (n);
}

int			db_load(const char *path)
{
	dprintf(g_mn.log, "[%ld] Loading %s...\n", time(NULL), path);
	DB.name = (char*)path;
	if ((DB.fd = open(path, O_RDWR | O_EXLOCK | O_SYMLINK)) < 0)
		PANIC(1);
	if (lseek(DB.fd, 0, SEEK_END) % 4096 > 0)
		PANIC(2);
	lseek(DB.fd, 0, SEEK_SET);
	if ((DB.map = MAP) == MAP_FAILED)
		PANIC(3);
	DBH = (void*)DB.map;
	if (DBH->ebyte != EBYTE)
		PANIC(4);
	if (DBH->x2a != 0x2a)
		PANIC(5);
	if (pthread_rwlock_init(&DB.lock, NULL) != 0)
		PANIC(6);
	return (0);
}
