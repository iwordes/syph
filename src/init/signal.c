/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 20:16:44 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/04 18:33:23 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

void	init_signal(void)
{
	uint8_t	i;

	sy_log("Initializing signal handlers...");
	i = 0;
	/*
	** NOTE: Disabled for debugging.
	while (i < 32)
		signal(i, SIG_IGN);
	*/
	signal(SIGTERM, uninit);
}
