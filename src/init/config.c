/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 12:19:16 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/04 18:33:06 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

/*
** TODO: Multiple DB support
** TODO: Actual configuration
*/

void	init_config(void)
{
	sy_log("Initializing config...");
	if (db_load("syph.db") != 0)
		FATAL("Could not load database \"syph.db\"!");
}
