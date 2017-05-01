/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 10:34:53 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/12 14:10:55 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libtp_.h>

void	tp_destroy(t_tp *tp)
{
	t_tp_job	ex;
	unsigned	i;

	i = 0;
	ex.ctx = NULL;
	ex.fn = tp__kill_thread;
	while (i < tp->nth)
	{
		tp_qpush(tp, tp__kill_thread, NULL);
		i += 1;
	}
	pthread_mutex_destroy(&WORQ.lock);
	pthread_cond_destroy(&WORQ.ev_new);
	pthread_cond_destroy(&WORQ.ev_done);
	free(tp->job.q);
	free(tp->th);
	free(tp);
}
