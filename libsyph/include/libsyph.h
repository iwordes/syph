/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsyph.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 13:53:01 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/03 18:40:46 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSYPH_H
# define LIBSYPH_H

# include <stdbool.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <string.h>


/*
** =============================================================================
** Private Structs
*/

typedef struct	s_sypair
{
	uint8_t		op;
	uint8_t		id;
}				t_sypair;

/*
** =============================================================================
** Public Structs
*/

typedef struct	s_syph
{
	uint8_t		ip[4];
	uint16_t	port;

	bool		be;
}				t_syph;

typedef struct	s_syfield
{
	uint8_t		type;

	uint8_t		f_pad_: 7;
	uint8_t		f_unique: 1;

	/*
	** The user does not need to provided the size field when creating a table.
	*/
	uint16_t	size;
	uint32_t	len;
}				t_syfield;

typedef struct	s_sytab
{
	uint8_t		label[33];
	uint8_t		schema_len;
	t_syfield	schema[255];

	/*
	** The user should never modify this once initialized.
	*/
	t_syph		*db;

	/*
	** Private
	*/
	uint32_t	id;
	uint32_t	ent_size;
}				t_sytab;

typedef struct	s_sycmp
{
	uint8_t		len;
	t_sypair	cmp[255];
	size_t		data_len;
	void		*data;
}				t_sycmp;

typedef struct	s_syasn
{
	uint8_t		len;
	t_sypair	asn[255];
	size_t		data_len;
	void		*data;
}				t_syasn;

/*
** =============================================================================
** Response
*/

typedef struct	s_sysel
{
	uint32_t	cnt;
	void		*data;
}				t_sysel;

/*
** =============================================================================
** Types
*/

typedef struct	s_sytype
{
	uint8_t		type;
	uint8_t		size_b;
}				t_sytype;

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

const t_sytype	g_sytype[11];

/*
** =============================================================================
** Functions
*/

t_syph			sy_connect(uint8_t ip[4], uint16_t port);

bool			sy_create(t_sytab *tab);

bool			sy_insert(const t_sytab *tab, uint32_t len, void *data);
t_sysel			*sy_select(t_sytab *tab, t_sycmp *cmp);
bool			sy_update(t_sytab *tab, t_sycmp *cmp, t_syasn *asn);
bool			sy_delete(const t_sytab *tab, const t_sycmp *cmp, uint32_t limit);

//TODO: Functions to create
int				sy__connit(t_syph *syph);
ssize_t			sy__read(int fd, void *mem, ssize_t n);

#endif
