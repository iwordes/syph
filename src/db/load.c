/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 12:32:16 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/05 17:38:47 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define MAP (mmap(NULL, blk * 4096, PROT_RW, MAP_SHARED, DB.fd, 0))
#define PANIC(N) return (panic(N))

static char	*g_emsg[] =
{
	"Failed to initialize database.",
	"Failed to open database.",
	"Invalid database: Size is not a multiple of 4096.",
	"Failed to get database size.",
	"Failed to map database into memory.",
	"Invalid database: Endian byte mismatch.",
	"Invalid database: Missing 0x2a at offset 1.",
	"Failed to allocate space for rwlock."
};

static int	panic(int n)
{
	LOG("\e[91mdb_load\e[0m");
	if (n > 6)
		pthread_rwlock_destroy(&DB.lock);
	if (n > 3)
		munmap(DB.map, (DBH->hd_blk + DBH->bd_blk) * 4096);
	if (n > 1)
		close(DB.fd);
	ERROR(g_emsg[n - 1]);
	return (n);
}

static U64	blocks_(int fd)
{
	uint32_t	bd;
	uint16_t	hd;
	uint8_t		be;

	lseek(fd, 0, SEEK_SET);
	if (read(fd, &be, 1) <= 0 || be != EBYTE)
		return (0);
	lseek(fd, 2, SEEK_SET);
	if (!sy_read(fd, &hd, 2) || !sy_read(fd, &bd, 4))
		return (0);
	lseek(fd, 0, SEEK_SET);
	return (hd + bd);
}

int			db_load(const char *path)
{
	U64		blk;

	LOG("\e[95mdb_load\e[0m");
	DB.name = (char*)path;
	if (access(path, F_OK) != 0 && db_init(path) != 0)
		PANIC(1);
	if ((DB.fd = open(path, O_RDWR | O_EXLOCK)) < 0)
		PANIC(2);
	if (lseek(DB.fd, 0, SEEK_END) % 4096 > 0)
		PANIC(3);
	if ((blk = blocks_(DB.fd)) == 0)
		PANIC(4);
	if ((DB.map = MAP) == MAP_FAILED)
		PANIC(5);
	DBH = (void*)DB.map;
	if (DBH->ebyte != EBYTE)
		PANIC(6);
	if (DBH->x2a != 0x2a)
		PANIC(7);
	if (pthread_rwlock_init(&DB.lock, NULL) != 0)
		PANIC(8);
	LOG("\e[92mdb_load\e[0m");
	return (0);
}
