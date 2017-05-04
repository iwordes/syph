/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unload.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 12:35:47 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/03 19:07:44 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

void	db_unload(t_db *db)
{
	pthread_rwlock_destroy(&db->lock);
	munmap(db->map, (db->head->hd_blk + db->head->bd_blk) * 4096);
	close(db->fd);
}
