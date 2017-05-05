/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <kdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 20:23:30 by kdavis            #+#    #+#             */
/*   Updated: 2017/05/04 21:30:51 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libsyph.h>

static void	pls_send(int sock, t_sytab *tab, t_sycmp *cmp, t_syasn *asn)
{
	write(sock, "\x32", 1);
	write(sock, &cmp->len, 1);
	write(sock, &asn->len, 1);
	write(sock, cmp->cmp, cmp->len * 2);
	write(sock, cmp->data, cmp->data_len);
	write(sock, asn->asn, asn->len * 2);
	write(sock, asn->data, asn->data_len);
}

bool		sy_update(t_sytab *tab, t_sycmp *cmp, t_syasn *asn)
{
	int			sock;
	uint32_t	cnt;
	int			r;

	if ((sock = sy__connit(tab->db)) < 0)
		return (false);
	pls_send(sock, tab, cmp, asn);
	r = sy_read(sock, &cnt, 4);
	close(sock);
	return (r == 4);
}
