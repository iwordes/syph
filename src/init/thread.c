/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 15:42:58 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/04 18:33:52 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

void	init_thread(void)
{
	sy_log("Initializing libtp...");
	if ((g_mn.tp = tp_create(4, 64)) == NULL)
		FATAL("Could not create thread pool!");
}
