/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsyph.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 13:53:01 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/05 19:47:13 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSYPH_H
# define LIBSYPH_H

# include <stdbool.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# define S_ADDR struct sockaddr_in

typedef S_ADDR	t_sysa;

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

/*
** A connection path to a SyphDB server.
**
** NOTE: *DO NOT* modify this after sy_connect() has been run.
** serv: The server to connect to in the form of "ip:port".
*/

typedef struct	s_syph
{
	char		*serv;

	uint32_t	ip;
	uint16_t	port;

	bool		be;
}				t_syph;

/*
** A field in the table's schema.
**
** type:  The type of the field. See #Types.
** flags: Don't matter right now.
** size:  The number of bytes one element takes up.
**  NOTE: size is set when sy_create() is run.
** len:   The number of elements the field consists of.
*/

typedef struct	s_syfield
{
	uint8_t		type;

	uint8_t		flags;

	uint16_t	size;
	uint32_t	len;
}				t_syfield;

/*
** Information about a table.
**
** NOTE: *DO NOT* reuse labels for different tables!
** NOTE: *DO NOT* modify these after sy_create() has been run.
** NOTE: The first field in the schema MUST be a U32.
**       { SYT_U32, SYF_UNIQ, 0, 1 }
**
** label:      The table's name, as on the server.
** schema_len: The number of fields in the table's schema.
** schema:     The table's schema, an array of fields.
** db:         The database this table resides on.
*/

typedef struct	s_sytab
{
	uint8_t		label[33];
	uint8_t		schema_len;
	t_syfield	schema[255];

	t_syph		*db;

	uint32_t	id;
	uint32_t	ent_size;
}				t_sytab;

/*
** A self-contained array of comparisons.
**
** len: The number of comparisons to do.
** cmp: The comparisons, in order:
**     op: See #Comparisons.
**     id: The field in your table to compare against.
** data_len: The number of bytes in data.
** data: The data to compare against. Must contain values like the table schema.
*/

typedef struct	s_sycmp
{
	uint8_t		len;
	t_sypair	cmp[255];
	size_t		data_len;
	void		*data;
}				t_sycmp;

/*
** A self-contained array of assignments.
**
** len: The number of assignments to do.
** cmp: The assignments, in order:
**     op: See #Assignments.
**     id: The field in your table to assign to.
** data_len: The number of bytes in data.
** data: The data to assign with. Must contain values like the table schema.
*/

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
	uint32_t	limit;

	uint32_t	cnt;
	t_sytab		*tab;
	void		*data;

	t_sycmp		cmp;
}				t_sysel;

/*
** =============================================================================
** Types
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
** Flags
*/

# define SYF_NONE 0
# define SYF_UNIQ 1

/*
** =============================================================================
** Comparisons
*/

# define SYC_EQU 0x40
# define SYC_NEQ 0x41

/*
** =============================================================================
** Assignments
*/

# define SYA_SET 0x50

/*
** =============================================================================
** Private Functions
*/

int				sy__connit(t_syph *syph);
ssize_t			sy__read(int fd, void *mem, ssize_t n);

/*
** =============================================================================
** Public Functions
*/

/*
** Initiate a connection to a SyphDB server.
** See t_syph for more info.
*/
bool			sy_connect(t_syph *syph);

/*
** Create or get an existing table.
** See t_sytab for more info.
*/
bool			sy_create(t_sytab *tab);

/*
** Interact with an existing table.
** All tables *must* be initiated with sy_create() before use.
** sy_insert: Add new data to a table.
**    tab: An initiated table.
**    len: The number of entries to insert.
**    data: An array of `len` entries.
**
** sy_select: Get data from a table.
**    sel.tab: An initated table.
**    sel.cmp: See t_cmp.
**    sel.limit: The maximum number of entries to retrieve.
**    sel.cnt: The number of entries successfully retrieved.
**    sel.data: A pointer to write retrieved entries to.
**    NOTE: sel.data should point to at least sel.limit entries of space!
**
** sy_update: Replace data in a table.
**    tab: An initiated table.
**    cmp: See t_cmp.
**    asn: See t_asn.
**
** sy_delete: Delete entries from a table.
**    tab: An initiated table.
**    cmp: See t_cmp.
**    lim: The maximum number of entries to delete.
*/
bool			sy_insert(const t_sytab *tab, uint32_t len, void *data);
bool			sy_select(t_sysel *sel);
bool			sy_update(const t_sytab *tab, const t_sycmp *cmp, t_syasn *asn);
bool			sy_delete(const t_sytab *tab, const t_sycmp *cmp, uint32_t lim);

#endif
