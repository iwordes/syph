/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 10:33:31 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/29 12:19:02 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

void	init(int *argc, char ***argv)
{
	if (argc > 1 && chdir(argv[1]) < 0)
		exit(errno);
	init_config();
	init_thread();
	init_socket();
}
