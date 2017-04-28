/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syph.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 10:45:45 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/27 20:12:13 by iwordes          ###   ########.fr       */
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

# define ERROR(MSG) sy_error(MSG)
# define FATAL(MSG) sy_fatal(MSG, __FILE__, __LINE__)
# define ASSERT(COND) if (!(COND)) FATAL("Assertion failed: " ##COND)

# define READ(F, T)

# define ZALT(T, N) (T*)calloc(sizeof(T) * (N))

# ifdef __BIG_ENDIAN__
#  define EBYTE 0xff
# else
#  define EBYTE 0x00
# endif

# define PROT_RW (PROT_READ | PROT_WRITE)

/*
**
** Error Codes
*/

# define DBE_RECV /* ? */
# define DBE_SEND /* ? */

# define DBE_READ DBE_RECV
# define DBE_WRITE DBE_SEND

/*
**
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

	uint16_t	pad;
	uint32_t	len;
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

	int			log;

	int			e;

	bool		bg;
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
