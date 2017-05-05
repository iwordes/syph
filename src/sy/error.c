/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 20:00:21 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/04 18:26:29 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

void	sy_error(const char *msg, const char *file, long line)
{
	dprintf(g_mn.log, "[%lu] \e[93m%s\e[0m:\e[96m%ld\e[0m: Error: %s\n",
		time(NULL), file, line, msg);
}
