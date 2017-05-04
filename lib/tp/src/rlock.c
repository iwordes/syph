/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rlock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 20:23:00 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/03 20:36:55 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libtp.h>

bool	tp_rlock(t_tp_rwl *lock)
{
	return (pthread_rwlock_rdlock(lock) == 0);
}
