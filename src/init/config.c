/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 12:19:16 by iwordes           #+#    #+#             */
/*   Updated: 2017/06/22 11:21:09 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

void	init_config(void)
{
	LOG("\e[1minit_config\e[0m");
	if (db_load("syph.db") != 0)
		FATAL("Could not load database \"syph.db\"!");
}
