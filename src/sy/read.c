/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 15:11:02 by iwordes           #+#    #+#             */
/*   Updated: 2017/06/18 12:24:03 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

bool	sy_read(int fd, void *raw_buff, ssize_t n)
{
	char	*buff;
	int		try;
	ssize_t	i;
	ssize_t	r;

	i = 0;
	try = 0;
	buff = raw_buff;
	while ((r = read(fd, buff + i, n - i)) != 0)
	{
		if (try == 20)
		{
			LOG("read() timeout");
			return (false);
		}
		if (r > 0)
			try = 0;
		else if (errno != EAGAIN)
			return (false);
		else
		{
			try += 1;
			sleep(1);
		}
		i += r;
	}
	return (r == 0 && i == n);
}
