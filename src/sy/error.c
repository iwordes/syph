/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 20:00:21 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/05 12:06:49 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

void	sy_error(const char *msg, const char *file, long line)
{
	lprintf("[%lu] \e[1;93m%s\e[0;1m:%ld\e[0m: %s\n",
		time(NULL), file + 4, line, msg);
}
