/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _kill_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 18:50:25 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/09 19:50:30 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libtp_.h>

void	tp__kill_thread(void *ctx)
{
	pthread_exit(ctx);
}