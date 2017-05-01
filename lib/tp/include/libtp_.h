/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libtp_.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 08:59:22 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/12 12:42:46 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBTP__H
# define LIBTP__H

# include "libtp.h"

# define WORQ tp->job
# define MALT(T, N) (T*)malloc(sizeof(T) * N)
# define ZALT(T, N) (T*)tp__zalloc(sizeof(T) * N)

void			tp__kill_thread(void *ctx);
void			*tp__work_loop(t_tp *tp);
void			*tp__zalloc(size_t n);
void			tp__bzero(void *mem, size_t n);

t_tp_job		tp_qpop(t_tp *tp);

#endif
