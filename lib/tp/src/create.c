/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 20:09:45 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/03 20:31:40 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libtp_.h>

t_tp	*mpanic_(t_tp *tp)
{
	if (tp && tp->job.q)
		free(tp->job.q);
	if (tp && tp->th)
		free(tp->th);
	if (tp)
		free(tp);
	return (NULL);
}

t_tp	*qpanic_(t_tp *tp, int flag)
{
	if (flag & 1)
		pthread_mutex_destroy(&WORQ.lock);
	if (flag & 2)
		pthread_cond_destroy(&WORQ.ev_new);
	if (flag & 4)
		pthread_cond_destroy(&WORQ.ev_done);
	return (mpanic_(tp));
}

t_tp	*tpanic_(t_tp *tp, unsigned n)
{
	unsigned	i;

	i = 0;
	while (i < n)
	{
		tp_qpush(tp, tp__kill_thread, NULL);
		i += 1;
	}
	return (qpanic_(tp, 7));
}

#define MFAIL(M) if ((M) == NULL) return (mpanic_(tp))
#define QFAIL(Q, F) if (Q) return (qpanic_(tp, F))

#define INITFN void *(*)(void*)

t_tp	*tp_create(unsigned nth, unsigned qlen)
{
	t_tp		*tp;
	unsigned	i;

	MFAIL(tp = ZALT(t_tp, 1));
	MFAIL(tp->th = ZALT(pthread_t, nth));
	MFAIL(tp->job.q = MALT(t_tp_job, qlen));
	QFAIL(pthread_mutex_init(&WORQ.lock, NULL), 0);
	QFAIL(pthread_cond_init(&WORQ.ev_new, NULL), 1);
	QFAIL(pthread_cond_init(&WORQ.ev_done, NULL), 3);
	i = 0;
	tp->nth = nth;
	tp->job.max = qlen;
	while (i < nth)
	{
		if (pthread_create(tp->th + i, NULL, (INITFN)tp__work_loop, tp))
			return (tpanic_(tp, i));
		i += 1;
	}
	return (tp);
}
