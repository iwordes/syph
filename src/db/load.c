/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 12:32:16 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/22 14:47:20 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define MAP (mmap(NULL, db->size, PROT_RW, MAP_SHARED, db->fd, 0))
#define PANIC(N) return (panic(db, N))

static int	panic(t_db *db, int n)
{
	if (n > 6)
		pthread_rwlock_destroy(&db->lock);
	if (n > 3)
		munmap(db->map, db->size * 4096);
	if (n > 1)
		close(db->fd);
	return (n);
}

int			db_load(t_db *db, const char *path)
{
	size_t	size;

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
