/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 10:34:53 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/03 20:33:11 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libtp_.h>

void	tp_destroy(t_tp *tp)
{
	unsigned	i;

	i = 0;
	tp_qwait(tp);
	while (i < tp->nth)
	{
		tp_qpush(tp, tp__kill_thread, tp);
		i += 1;
	}
	tp_qwait(tp);
	pthread_mutex_destroy(&WORQ.lock);
	pthread_cond_destroy(&WORQ.ev_new);
	pthread_cond_destroy(&WORQ.ev_done);
	free(tp->job.q);
	free(tp->th);
	free(tp);
}
