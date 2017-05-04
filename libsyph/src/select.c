/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 19:09:31 by kdavis            #+#    #+#             */
/*   Updated: 2017/05/03 20:21:35 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libsyph.h>

static void	write_to_sock(int sock, const t_sytab *tab, const t_sycmp *cmp,
		uint32_t limit)
{
	write(sock, "\x31", 1);
	write(sock, &tab->id, 4);
	write(sock, &limit, 4);
	write(sock, &tab->schema_len, 1);
	write(sock, &cmp->len, 1);
	write(sock, cmp->cmp, cmp->len * sizeof(t_sypair));
	write(sock, cmp->data, cmp->data_len);
}

t_sysel	*sy_select(const t_sytab *tab, const t_sycmp *cmp, uint32_t limit)
{
	t_sysel	*ret;
	
	if (!(ret = calloc(1, sizeof(*ret))))
		return (NULL);
	if (tab->db->be)
		limit = htonl(limit);
	sock = sy__connit(tab->db);
	write_to_sock(sock, tab, cmp, limit); //Condense writing to one helper function
	if ((sy__read(sock, &ret->cnt, 4) == 4) &&
			sy__read(sock, ret->data, ret->cnt * tab->ent_size)
			== ret->cnt * tab->ent_size) 
		return (ret);
	free(ret);
	return (NULL);
}
