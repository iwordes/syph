/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libarg.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 09:53:15 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/08 19:28:11 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBARG_H
# define LIBARG_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

# define T_ARG0 void (*)()
# define T_ARG1 void (*)(char*)

/*
** # define USAGE ""
*/

typedef struct	s_arg
{
	char		*name;
	void		*fn;
	bool		param;
}				t_arg;

void			arg_parse(int *argc, char ***argv, t_arg *arg);

#endif
