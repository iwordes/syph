/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 20:44:16 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/04 19:21:02 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

static t_db_head	g_head =
{
	EBYTE,
	0x2a,

	1,
	0U,

	1,
	1,

	0
};

static char			*g_err[] =
{
	"Could not open database.",
	"Could not grow database.",
	"Could not write header."
};

int					panic_(int fd, int n)
{
	if (n > 1)
		close(fd);
	ERROR(g_err[n - 1]);
	return (n);
}

#define PANIC(N) return (panic_(fd, N))

int					db_init(const char *path)
{
	int		fd;

	if ((fd = open(path, O_RDWR| O_CREAT | O_EXLOCK, 0600)) < 0)
		PANIC(1);
	if (ftruncate(fd, 4096) < 0)
		PANIC(2);
	if (write(fd, &g_head, sizeof(g_head)) < 0)
		PANIC(3);
	close(fd);
	return (0);
}
