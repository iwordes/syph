/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qwait.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 20:20:20 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/03 20:30:13 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libtp_.h>

void	tp_qwait(t_tp *tp)
{
	tp_mlock(&WORQ.lock);
	while (WORQ.undone != 0)
		tp_evwait(&WORQ.ev_done, &WORQ.lock);
	tp_munlock(&WORQ.lock);
}
