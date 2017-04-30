/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 12:19:16 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/29 20:22:36 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

/*
** TODO: Multiple DB support
** TODO: Actual configuration
*/

void	init_config(void)
{
	if (db_load("syph.db") != 0)
		exit(DBE_LOAD);
}
