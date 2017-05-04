/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 15:42:58 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/03 20:19:59 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

void	init_thread(void)
{
	if ((g_mn.tp = tp_create(4, 64)) == NULL)
		FATAL("Could not create thread pool!");
}
