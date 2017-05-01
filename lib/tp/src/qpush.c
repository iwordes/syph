/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qpush.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 20:19:18 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/12 12:38:12 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libtp_.h>

bool	tp_qpush(t_tp *tp, void *job, void *ctx)
{
	tp_lock(&WORQ.lock);
	if (WORQ.len == WORQ.max)
	{
		tp_unlock(&WORQ.lock);
		return (false);
	}
	WORQ.len += 1;
	WORQ.undone += 1;
	WORQ.q[WORQ.b].fn = job;
	WORQ.q[WORQ.b].ctx = ctx;
	WORQ.b = (WORQ.b + 1) % WORQ.max;
	tp_evfire(&WORQ.ev_new);
	tp_unlock(&WORQ.lock);
	return (true);
}
