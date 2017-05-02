/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syph.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 10:45:45 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/02 14:35:08 by iwordes          ###   ########.fr       */
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

# define TAB_HD_BLK 1
# define TAB_BD_BLK (1024 * 1024) / 4096

# ifdef __BIG_ENDIAN__
#  define EBYTE 0xff
# else
#  define EBYTE 0x00
# endif

# define PROT_RW (PROT_READ | PROT_WRITE)

/*
** =============================================================================
** Utils
*/

# define ERROR(MSG) sy_error(MSG, __FILE__, __LINE__)
# define FATAL(MSG) sy_fatal(MSG, __FILE__, __LINE__)
# define ASSERT(COND) if (!(COND)) FATAL("Assertion failed: " ##COND)

# define TAB_BD(T) ((uint8_t*)(T) + (T)->hd_blk * 4096)

# define ZALT(T, N) (T*)calloc(sizeof(T) * (N))

/*
** =============================================================================
** Types
*/

# define I8 int8_t
# define I16 int16_t
# define I32 int32_t
# define I64 int64_t

# define U8 uint8_t
# define U16 uint16_t
# define U32 uint32_t
# define U64 uint64_t

/*
** =============================================================================
** Error Codes
*/

# define DBERROR(CODE) sy_dberror(CODE)

# define DBE 1
# define DBE_OOM 2

# define DBE_CHDIR 10
# define DBE_O_LOG 11

# define DBE_SACC 20 /* ? socket-accept */
# define DBE_RECV /* ? socket-recv */
# define DBE_SEND /* ? socket-send */

# define DBE_READ DBE_RECV
# define DBE_WRITE DBE_SEND

/*
** =============================================================================
** Conversion
*/

# ifdef __BIG_ENDIAN__
#  define H64N(N) (N)
#  define N64H(N) (N)
# else
// TODO
#  define H64N1(N) ((N & 0xff) << 56) | ((N & 0xff00) << 48)
#  define H64N2(N) ((N & 0xff0000) << 40) | ((N & 0xff000000) << 8)
#  define H64N3(N) ((N & (255 << 32)) >> 8) | ((N & (255 << 40)) >> 16)
#  define H64N4(N) ((N & (255 << 56)) >> 56) | (N & (255 << 48) >> 40)
// TODO

#  define H64N(N) ((H64N1(N) | H64N2(N) | H64N3(N) | H64N4(N)))
#  define N64H(N) H64N(N)
# endif

# define H32N(N) htonl(N)
# define N32H(N) ntohl(N)
# define H16N(N) htons(N)
# define N16H(N) ntohs(N)

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

	uint32_t	table_cnt;
	uint32_t	table[2];
}				t_db_head;

typedef struct	s_field
{
	uint8_t		type;

	uint8_t		f_pad_: 7;
	uint8_t		f_unique: 1;

	uint16_t	size;
	uint32_t	len;
}				t_field;

typedef struct	s_tab_head
{
	uint32_t	id;
	uint32_t	len;

	uint32_t	next_id;
	uint32_t	entry_size;

	uint32_t	bd_blk;
	uint16_t	hd_blk;

	uint8_t		label[33];

	uint8_t		schema_len;
}				t_tab_head;

typedef struct	s_db
{
	uint8_t		*map;
	size_t		size;
	int			fd;

	t_tp_rwl	lock;

	t_db_head	*head;


	uint32_t	tlen;
	uint32_t	tmem;
	t_tbl_head	**tbl;
}				t_db;

typedef struct	s_main
{
	t_db		db;
	t_tp		*tp;

	int			log;

	int			e;

	bool		bg;
}				t_main;

/*
** =============================================================================
** Requests
*/

typedef struct	s_req21
{
	U8			label[33];
	U8			schema_len;
}				t_req21;

typedef struct	s_req30
{
	uint32_t	tid;
	uint32_t	limit;
	uint8_t		field_len;

	uint8_t		field[255];
}				t_req30;

typedef struct	s_req31
{
	uint32_t	tid;
	uint32_t	limit;
	uint8_t		field_len;
	uint8_t		cmp_len;
	uint8_t		order_len;

	uint8_t		field[255];
	uint8_t		*tab_start;
	U32			offset[255];
	U8			*entry;
}				t_req31;

typedef struct	s_req32
{
	uint32_t	tid;
	uint8_t		cond_len;
	uint8_t		assign_len;
}				t_req32;

typedef struct	s_req33
{
	uint32_t	tid;
	uint32_t	limit;
	uint8_t		cond_len;
}				t_req33;

/*
** =============================================================================
** Reqiter
*/

typedef struct	s_tabsel
{

}				t_tabsel;

typedef struct	s_tabupd
{

}				t_tabupd;

typedef struct	s_tabdel
{

}				t_tabdel;

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
