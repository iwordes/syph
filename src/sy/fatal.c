/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 15:12:35 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/04 23:29:16 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

void	sy_fatal(const char *msg, const char *file, long line)
{
	dprintf(g_mn.log,
		"[%lu] \e[91m%s\e[0m:\e[96m%ld\e[0m: %s\n",
		time(NULL), file, line, msg);
	exit(1);
}
