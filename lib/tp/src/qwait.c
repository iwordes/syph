/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qwait.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 20:20:20 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/12 12:44:28 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libtp_.h>

/*
** TODO: Wait for specific tasks
** (create a per-job condition)
**
** Would return a t_tp_evt* for the job in question.
** void	*tp_qpush(t_tp *tp, void *job, void *ctx);
**
** ...
**
** tp_qwait(tp, job*, ..., NULL)
**
** job
** {
**     t_tp_evt	done;
**     ...
** }
*/

void	tp_qwait(t_tp *tp)
{
	tp_lock(&WORQ.lock);
	while (WORQ.undone != 0)
		tp_evwait(&WORQ.ev_done, &WORQ.lock);
	tp_unlock(&WORQ.lock);
}
