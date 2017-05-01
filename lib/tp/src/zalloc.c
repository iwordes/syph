/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zalloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 18:37:39 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/12 12:32:57 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libtp_.h>

void	*tp__zalloc(size_t n)
{
	void	*mem;

	if ((mem = malloc(n)) == NULL)
		return (NULL);
	tp__bzero(mem, n);
	return (mem);
}
