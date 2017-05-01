/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_queue_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 08:56:15 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/09 20:05:33 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libtp.h>

void	tp_exec_queue_add(t_tp *tp, void *job, void *context)
{
	tp_qpush(tp, job, context);
}
