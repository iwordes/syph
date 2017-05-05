/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 16:01:01 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/04 21:21:01 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libsyph.h>

bool	sy_delete(const t_sytab *tab, const t_sycmp *cmp, uint32_t limit)
{
	int			sock;
	int			r;

	sock = sy__connit(tab->db);
	write(sock, "\x33", 1);
	write(sock, &tab->id, 4);
	write(sock, &limit, 4);
	write(sock, &cmp->len, 1);
	write(sock, cmp->cmp, cmp->len * sizeof(t_sypair));
	write(sock, cmp->data, cmp->data_len);
	r = sy__read(sock, &limit, 4);
	close(sock);
	return (r == 4);
}
