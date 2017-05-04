/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 15:42:58 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/03 19:12:29 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

void	init_thread(void)
{
	if ((g_mn.tp = tp_create(4, 64)) == NULL)
		FATAL("Could not create thread pool!");
}
