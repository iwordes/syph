/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncpu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 08:35:00 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/09 09:23:21 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libtp.h>

/*
** Return the number of processors the current computer has.
** Counts logical cores as well as physical cores.
*/

int		tp_ncpu(void)
{
	return (sysconf(_SC_NPROCESSORS_ONLN));
}
