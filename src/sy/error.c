/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 20:00:21 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/04 14:53:50 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

void	sy_error(const char *msg, const char *file, long line)
{
	dprintf(g_mn.log, "[%lu] %s:%ld: Error: %s\n", time(NULL), file, line, msg);
}
