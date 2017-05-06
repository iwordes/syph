/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_read.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 15:00:32 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/05 18:53:45 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libsyph.h>

ssize_t		sy__read(int fd, void *mem, ssize_t n)
{
	ssize_t		i;
	ssize_t		r;

	i = 0;
	r = 1;
	while (i < n && r > 0)
	{
		r = read(fd, (char*)mem + i, n - i);
		if (r < 0)
			return (-1);
		i += r;
	}
	return (i);
}
