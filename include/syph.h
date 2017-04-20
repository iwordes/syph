/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syph.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 10:45:45 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/19 20:09:21 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYPH_H
# define SYPH_H

# include <arpa/inet.h>
# include <signal.h>
# include <stdio.h>
# include <sys/socket.h>
# include <unistd.h>

# include <libarg.h>

# define ERROR(MSG) sy_error(MSG, __FILE__, __LINE__)
# define ASSERT(COND) if (!(COND)) ERROR("Assertion failed: " ##COND)

/*
** =============================================================================
** Datatypes
*/

typedef struct	s_field
{
	uint8_t		type;

	uint8_t		f_id: 1;
	uint8_t		f_pad: 5;
	uint8_t		f_null: 1;
	uint8_t		f_unique: 1;

	int8_t		label[30];
}				t_field;

typedef struct	s_table
{
	uint32_t	id;
	uint8_t		field_cnt;
	t_field		*field;


}				t_table;

typedef struct	s_db
{
	uint32_t	table_cnt;
	t_table		*table;

	int			fd;
	int			jnl;
}				t_db;

typedef struct	s_main
{
	// ...
	t_db		*db;

	bool		daemon;
	bool		v;
}				t_main;

/*
** =============================================================================
** Main
*/

void			init(int *argc, char ***argv);
void			uninit(void);

/*
** =============================================================================
** Database
*/

// ...

/*
** =============================================================================
** Request
*/

// ...

/*
** =============================================================================
** Response
*/

// ...

/*
** =============================================================================
** Syph
*/

// ...

#endif
