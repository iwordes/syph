/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <kdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 20:23:30 by kdavis            #+#    #+#             */
/*   Updated: 2017/05/05 18:59:06 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libsyph.h>

static void	pls_send(int sock, const t_sytab *tab,
	const t_sycmp *cmp, const t_syasn *asn)
{
	write(sock, "\x32", 1);
	write(sock, &tab->id, 4);
	write(sock, &cmp->len, 1);
	write(sock, &asn->len, 1);
	write(sock, cmp->cmp, cmp->len * 2);
	write(sock, cmp->data, cmp->data_len);
	write(sock, asn->asn, asn->len * 2);
	write(sock, asn->data, asn->data_len);
}

bool		sy_update(const t_sytab *tab, const t_sycmp *cmp, t_syasn *asn)
{
	int			sock;
	uint32_t	cnt;
	int			r;

	if ((sock = sy__connit(tab->db)) < 0)
		return (false);
	pls_send(sock, tab, cmp, asn);
	r = sy__read(sock, &cnt, 4);
	close(sock);
	return (r == 4);
}
