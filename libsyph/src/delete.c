/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 16:01:01 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/03 18:35:47 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libsyph.h>

bool	sy_delete(const t_sytab *tab, const t_sycmp *cmp, uint32_t limit)
{
	int			sock;
	int			r;
	uint32_t	tmp;

	tmp = cmp->len;
	if (tab->db->be)
	{
		limit = htonl(limit);
		tmp = htonl(cmp->len);
	}
	sock = sy__connit(tab->db);
	write(sock, "\x33", 1);
	write(sock, &limit, 4);
	write(sock, &tmp, 4);
	write(sock, cmp->cmp, cmp->len * sizeof(t_sypair));
	write(sock, cmp->data, cmp->data_len);
	r = sy__read(sock, &limit, 4);
	close(sock);
	return (r == 4);
}
