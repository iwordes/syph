/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 20:00:21 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/19 20:11:14 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

/*
** TODO: sy_fatal(const char *msg, const char *file, int line)
**       ^ exits on call
*/

void	sy_error(const char *msg, const char *file, int line)
{
	dprintf(g_mn.log, "[%lu] %s:%d: Error: %s\n", time(NULL), file, line, msg);
	exit(1);
}
