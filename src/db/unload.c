/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unload.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 12:35:47 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/03 20:18:38 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

void	db_unload(void)
{
	pthread_rwlock_destroy(&DB.lock);
	munmap(DB.map, (DBH->hd_blk + DBH->bd_blk) * 4096);
	close(DB.fd);
}
