/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syph.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 10:45:45 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/22 12:26:20 by iwordes          ###   ########.fr       */
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
# include <libtp.h>

# define ERROR(MSG) sy_error(MSG, __FILE__, __LINE__)
# define ASSERT(COND) if (!(COND)) ERROR("Assertion failed: " ##COND)

# define ZALT(T, N) (T*)calloc(sizeof(T) * (N))

/*
** =============================================================================
** Datatypes
*/

typedef struct	s_db_head
{
	uint8_t		ebyte;
	uint8_t		x2a;

	uint16_t	hd_len;

	uint32_t	next_id;
	uint32_t	next_off;

	uint32_t	table_len;
	uint32_t	table[2];
}				t_db_head;

typedef struct	s_field
{
	uint8_t		type;

	uint8_t		f_pad_: 7;
	uint8_t		f_unique: 1;
}				t_field;

typedef struct	s_tbl_head
{
	uint32_t	id;
	uint32_t	len;
	uint64_t	next_id;

	uint32_t	bd_len;
	uint16_t	hd_len;

	uint8_t		label[33];

	uint8_t		field_len;
	t_field		field;
}				t_tbl_head;

typedef struct	s_db
{
	uint32_t	table_cnt;
	t_table		*table;

	uint8_t		*map;
	size_t		len;

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
