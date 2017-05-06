/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syph.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 10:45:45 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/05 21:47:23 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYPH_H
# define SYPH_H

# include <arpa/inet.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <strings.h>
# include <sys/mman.h>
# include <sys/socket.h>
# include <sys/stat.h>
# include <time.h>
# include <unistd.h>

# include <libtp.h>

# define DB g_mn.db
# define DBH DB.head

# define DB_BLK (DBH->hd_blk + DBH->bd_blk)

# define TAB_HD_BLK 1
# define TAB_BD_BLK (1024 * 1024) / 4096

# define TAB_BLK (TAB_HD_BLK + TAB_BD_BLK)

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

/*
** #define LOG(A...) lprintf(DBM_L ##A)
** #define ERROR(A...) lprintf(DBM_E M, time(NULL), __FILE__, __LINE__, ##A)
** #define FATAL(A...) lprintf(DBM_F M, time(NULL), __FILE__, __LINE__, ##A)
*/

# define LOG(MSG) sy_log(MSG)
# define ERROR(MSG) sy_error(MSG, __FILE__, __LINE__)
# define FATAL(MSG) sy_fatal(MSG, __FILE__, __LINE__)

# define ASSERT(COND) if (!(COND)) FATAL("Assertion failed: " ##COND)

# define TAB_BD(T) ((uint8_t*)(T) + (T)->hd_blk * 4096)

# define ZALT(T, N) (T*)calloc((N), sizeof(T))
# define RALT(M, T, N) (T*)realloc(M, sizeof(T) * (N))
# define DRALT(M, T, N) (M = (T*)reallocf(M, sizeof(T) * (N)))

# define MIN(N1, N2) (((N1) <= (N2)) ? (N1) : (N2))

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
** Type codes
*/

# define SYT_U8   0x00
# define SYT_U16  0x01
# define SYT_U32  0x02
# define SYT_U64  0x03
# define SYT_I8   0x04
# define SYT_I16  0x05
# define SYT_I32  0x06
# define SYT_I64  0x07
# define SYT_UTF8 0x0d

# define SYT_F32  0x10
# define SYT_F64  0x11

/*
** =============================================================================
** Error Codes
*/

# define DBERROR(CODE) sy_dberror(CODE)

# define DBE 1
# define DBE_OOM 2

# define DBE_CHDIR 10
# define DBE_O_LOG 11
# define DBE_LLOCK 12

# define DBE_SACC 20
# define DBE_RECV
# define DBE_SEND

# define DBE_READ DBE_RECV
# define DBE_WRITE DBE_SEND

/*
** =============================================================================
** Datatypes
*/

typedef struct	s_db_head
{
	uint8_t		ebyte;
	uint8_t		x2a;

	uint16_t	hd_blk;
	uint32_t	bd_blk;

	uint32_t	next_id;
	uint32_t	next_off;

	uint32_t	tab_cnt;
}				t_db_head;

typedef struct	s_field
{
	uint8_t		type;

	uint8_t		f_pad_: 7;
	uint8_t		f_unique: 1;

	uint16_t	size;
	uint32_t	len;
}				t_field;

typedef struct	s_tab
{
	uint32_t	id;
	uint32_t	len;

	uint32_t	next_id;
	uint32_t	ent_size;

	uint32_t	bd_blk;
	uint16_t	hd_blk;

	uint8_t		label[33];

	uint8_t		schema_len;
}				t_tab;

typedef struct	s_db
{
	char		*name;
	uint8_t		*map;
	size_t		size;
	int			fd;

	t_tp_rwl	lock;

	t_db_head	*head;

	uint32_t	tlen;
	uint32_t	tmem;
	t_tab		**tab;
}				t_db;

typedef struct	s_main
{
	t_db		db;
	t_tp		*tp;

	int			sock;
	int			log;

	uint16_t	port;

	int			e;

	bool		bg;

	t_tp_mut	llock;
}				t_main;

typedef struct	s_op
{
	uint8_t		op;
	void		(*fn)(int);
}				t_op;

typedef struct	s_cmp
{
	uint8_t		op;
	bool		(*fn)(t_field*, U8*, U8*);
}				t_cmp;

typedef struct	s_asn
{
	uint8_t		op;
	void		(*fn)(t_field*, U8*, U8*);
}				t_asn;

typedef void	(*t_asnfn)(t_field*, U8*, U8*);
typedef bool	(*t_cmpfn)(t_field*, U8*, U8*);

/*
** =============================================================================
** Requests
*/

typedef struct	s_pair
{
	U8			op;
	U8			id;
}				t_pair;

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
	uint8_t		pad1;

	t_pair		cmp[255];
	uint16_t	pad2;
	U8			*cmp_val;

	uint32_t	cnt;
	int			sock;
}				t_req31;

typedef struct	s_req32
{
	uint32_t	tid;
	uint8_t		cmp_len;
	uint8_t		asn_len;

	t_pair		cmp[255];
	uint16_t	pad1;
	U8			*cmp_val;

	t_pair		asn[255];
	uint16_t	pad2;
	U8			*asn_val;

	uint32_t	cnt;
}				t_req32;

typedef struct	s_req33
{
	uint32_t	tid;
	uint32_t	limit;
	uint8_t		cmp_len;

	t_pair		cmp[255];
	uint16_t	pad1;
	U8			*cmp_val;

	uint32_t	cnt;
}				t_req33;

/*
** =============================================================================
** Reqiter
*/

typedef struct	s_tabmat
{
	uint32_t	cnt;
	t_pair		cmp[255];
	uint8_t		pad1;
	uint8_t		cmp_len;
	U8			*cmp_val;
}				t_tabmat;

typedef struct	s_getpair
{
	t_tab		*tab;
	int			sock;
}				t_getpair;

/*
** =============================================================================
** Main
*/

void			init(int *argc, char ***argv);
void			loop(void);
void			uninit(int z);

t_main			g_mn;

t_op			g_op[8];
t_asn			g_asn[2];
t_cmp			g_cmp[3];

/*
** =============================================================================
** Database
*/

void			*db_blk(uint32_t at);

bool			db_grow(uint32_t at, uint32_t skip);
int				db_init(const char *path);
int				db_load(const char *path);
void			db_rlock(void);
void			db_unload(void);
void			db_unlock(void);
void			db_wlock(void);

/*
** =============================================================================
** Operation
*/

void			op_21_create(int sock);
void			op_2f_delete(int sock);

void			op_30_insert(int sock);
void			op_31_select(int sock);
void			op_32_update(int sock);
void			op_33_delete(int sock);

bool			op_40_equ(t_field *meta, U8 *lhs, U8 *rhs);
bool			op_41_neq(t_field *meta, U8 *lhs, U8 *rhs);

void			op_50_set(t_field *meta, U8 *lhs, U8 *rhs);

void			op_ff_ping(int sock);

/*
** =============================================================================
** Table
*/

t_tab			*table(uint32_t id);
t_tab			*tab_by_label(uint8_t label[33]);

uint8_t			*tab_ent(t_tab *tab, uint32_t id);
t_field			*tab_field(t_tab *tab, uint8_t id);
off_t			tab_foff(t_tab *tab, uint8_t id);

void			tab_foreach(t_tab *tab, void *fn, void *ctx);

void			tab_match(t_tab *tab, uint8_t *ent, t_req31 *req);
void			tab_select(t_tab *tab, uint8_t *ent, t_req31 *req);
void			tab_update(t_tab *tab, uint8_t *ent, t_req32 *req);
void			tab_delete(t_tab *tab, uint8_t *ent, t_req33 *req);

/*
** =============================================================================
** Syph
*/

void			init_config(void);
void			init_signal(void);
void			init_socket(void);
void			init_thread(void);

t_asnfn			sy_asn(uint8_t op);
t_cmpfn			sy_cmp(uint8_t op);

int				lprintf(const char *msg, ...);

void			sy_error(const char *msg, const char *file, long line);
void			sy_fatal(const char *msg, const char *file, long line);
void			sy_log(const char *msg);

char			*sy_time(void);

bool			sy_getpair(t_getpair p, U8 len, t_pair pair[255], U8 **val);

bool			sy_read(int fd, void *buff, ssize_t n);

#endif
