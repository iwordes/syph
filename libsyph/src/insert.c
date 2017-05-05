/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 16:39:21 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/05 14:42:56 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libsyph.h>
#include <stdio.h>

#define DAT ((char*)data)

static void	pls_send(int sock, const t_sytab *tab, uint32_t cnt, void *data)
{
	uint8_t		id;

	write(sock, "\x30", 1);

	write(sock, &tab->id, 4);
	write(sock, &cnt, 4);
	write(sock, &tab->schema_len, 1);
	id = ~0;
	while (++id < tab->schema_len)
		write(sock, &id, 1);


	write(sock, data, cnt * tab->ent_size);
}

#define I(i) *(unsigned*)(DAT + 142 * i)
#define U(i) (DAT + 142 * i + 4)
#define P(i) (DAT + 142 * i + 13)

bool		sy_insert(const t_sytab *tab, uint32_t cnt, void *data)
{
	int			sock;
	int			r;

	if ((sock = sy__connit(tab->db)) < 0)
		return (false);

	write(1, data, 80 * 3);
	while(1);

	printf("-> %u '%-8s' '%-64s'\n", I(0), U(0), P(0));
	printf("-> %u '%-8s' '%-64s'\n", I(1), U(1), P(1));
	printf("-> %u '%-8s' '%-64s'\n", I(2), U(2), P(2));

	pls_send(sock, tab, cnt, data);
	r = sy__read(sock, &cnt, 4);
	close(sock);
	return (r == 4);
}
