/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 10:57:31 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/22 12:13:45 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

/*
** TODO: Make this code safer; protect ftruncate/mmap
*/

bool	db_grow(t_db *db, uint64_t offset)
{
	void		*zero;

	if (db->blocks * 4096 < offset)
	{
		munmap(db->map, db->blocks * 4096);
		while (db->blocks * 4096 < offset)
		{
			db->blocks *= 2;
			ftruncate(db->fd, db->blocks * 4096);
		}
		db->map = mmap(NULL, db->blocks * 4096, PROT_READ | PROT_WRITE,
			MAP_SHARED, db->fd, 0);
	}
	return (true);
}
