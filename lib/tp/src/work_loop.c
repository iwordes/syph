/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 09:47:10 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/03 20:27:25 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libtp_.h>

void	done_(t_tp *tp)
{
	tp_mlock(&WORQ.lock);
	WORQ.undone -= 1;
	if (WORQ.undone == 0)
		tp_evfire(&WORQ.ev_done);
	tp_munlock(&WORQ.lock);
}

void	*tp__work_loop(t_tp *tp)
{
	t_tp_job	job;

	while (1)
	{
		job = tp_qpop(tp);
		job.fn(job.ctx);
		done_(tp);
	}
	return (tp);
}
