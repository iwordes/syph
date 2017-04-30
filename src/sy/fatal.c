/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 15:12:35 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/29 20:19:24 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	sy_fatal(const char *msg, const char *file, int line)
{
	dprintf(g_mn.log, "[%lu] %s:%d: FATAL: %s\n", time(NULL), file, line, msg);
	uninit(0);
	exit(1);
}
