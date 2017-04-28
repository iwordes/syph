/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 12:32:16 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/27 15:39:13 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define MAP (mmap(NULL, db->size, PROT_RW, MAP_SHARED, db->fd, 0))
#define PANIC(N) return (panic(db, N))

static char	*g_emsg[] =
{
	"Failed to open database.",
	"Invalid database: Size is not a multiple of 4096.",
	"Failed to map database into memory.",
	"Invalid database: Endian byte mismatch.",
	"Invalid database: Missing 0x2a at offset 1.",
	"Failed to allocate space for rwlock."
};

static int	panic(t_db *db, int n)
{
	if (n > 6)
		pthread_rwlock_destroy(&db->lock);
	if (n > 3)
		munmap(db->map, db->size * 4096);
	if (n > 1)
		close(db->fd);
	sy_error(g_emsg[n - 1]);
	return (n);
}

int			db_load(t_db *db, const char *path)
{
	size_t	size;

	dprintf(g_mn.log, "[%d] Loading %s...\n", time(NULL), path);
	if ((db->fd = open(path, O_RDWR | O_EXLOCK | O_SYMLINK)) < 0)
		PANIC(1);
	if ((size = lseek(db->fd, 0, SEEK_END)) % 4096 > 0)
		PANIC(2);
	db->size = size / 4096;
	lseek(db->fd, 0, SEEK_SET);
	if ((db->map = MAP) == MAP_FAILED)
		PANIC(3);
	db->head = (t_db_head*)db->map;
	if (db->head->ebyte != EBYTE)
		PANIC(4);
	if (db->head->x2a != 0x2a)
		PANIC(5);
	if (pthread_rwlock_init(&db->lock, NULL) != 0)
		PANIC(6);
	return (0);
}
