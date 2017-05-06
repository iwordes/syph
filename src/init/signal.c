/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 20:16:44 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/05 19:16:35 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

static void	hook(int sig)
{
	if (sig == SIGSEGV || sig == SIGBUS)
		FATAL(strsignal(sig));
	else
		ERROR(strsignal(sig));
}

void		init_signal(void)
{
	uint8_t	i;

	LOG("\e[1minit_signal\e[0m");
	i = 0;
	while (++i < 32)
		signal(i, hook);
	signal(SIGINT, uninit);
}
