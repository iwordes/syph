/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 20:16:44 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/04 21:51:21 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

void	init_signal(void)
{
	uint8_t	i;

	sy_log("Initializing signal handlers...");
	i = 0;
	while (i < 32)
	{
		signal(i, SIG_IGN);
		i += 1;
	}
	signal(SIGINT, uninit);
}
