/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libarg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 10:35:27 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/08 18:00:17 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libarg.h"

#define ARGC (*argc)
#define ARGV (*argv)
#define ARG (**argv)

static bool		strequ_(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1 += 1;
		s2 += 1;
	}
	return (*s2 == *s1);
}

static t_arg	*arg_(char *arg, t_arg *args)
{
	if (!arg || !args)
	{
		write(1, USAGE, sizeof(USAGE) - 1);
		exit(2);
	}
	while (args->name)
	{
		if (strequ_(args->name, arg))
			return (args);
		args++;
	}
	arg_(NULL, NULL);
	return (NULL);
}

static void		short_(int *argc, char ***argv, t_arg *args)
{
	char	buff[2];
	t_arg	*arg;
	int		i;

	i = 1;
	buff[1] = 0;
	while ((*ARGV)[i])
	{
		buff[0] = (*ARGV)[i];
		arg = arg_(buff, args);
		if (arg->param && (ARGC == 1 || (*ARGV)[i + 1] != 0))
			arg_(NULL, NULL);
		else if (!arg->param)
			((T_ARG0)arg->fn)();
		else
		{
			ARGC -= 1;
			((T_ARG1)arg->fn)(*(ARGV += 1));
			break ;
		}
		i += 1;
	}
}

static void		long_(int *argc, char ***argv, t_arg *args)
{
	t_arg		*arg;

	if ((arg = arg_(*ARGV, args))->param && ARGC == 1)
		arg_(NULL, NULL);
	else if (!arg->param)
		((T_ARG0)arg->fn)();
	else
	{
		ARGC--;
		((T_ARG1)arg->fn)(*(ARGV += 1));
	}
}

void			arg_parse(int *argc, char ***argv, t_arg *args)
{
	ARGC -= 1;
	ARGV += 1;
	while (ARGC != 0 && (*ARGV)[0] == '-')
	{
		if (ARG[1] != '-')
			short_(argc, argv, args);
		else if (ARG[2] == 0)
			break ;
		else
			long_(argc, argv, args);
		ARGC--;
		ARGV++;
	}
}
