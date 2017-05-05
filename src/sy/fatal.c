/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 15:12:35 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/05 12:06:53 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

void	sy_fatal(const char *msg, const char *file, long line)
{
	lprintf("[%lu] \e[1;91m%s\e[0;1m:%ld\e[0m: %s\n",
		time(NULL), file + 4, line, msg);
	exit(1);
}
