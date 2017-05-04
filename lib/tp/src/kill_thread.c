/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 18:50:25 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/03 20:30:46 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libtp_.h>

void	tp__kill_thread(t_tp *tp)
{
	tp_mlock(&WORQ.lock);
	WORQ.undone -= 1;
	if (WORQ.undone == 0)
		tp_evfire(&WORQ.ev_done);
	tp_munlock(&WORQ.lock);
	pthread_exit(NULL);
}
