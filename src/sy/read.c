/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 15:11:02 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/29 15:14:39 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

bool	sy_read(int fd, void *raw_buff, ssize_t n)
{
	char	*buff;
	ssize_t	i;
	ssize_t	r;

	i = 0;
	buff = raw_buff;
	while ((r = read(fd, buff + i, n - i)) > 0)
		i += r;
	return (r == 0 && i == n);
}
