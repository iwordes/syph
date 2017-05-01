/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 12:13:51 by kdavis            #+#    #+#             */
/*   Updated: 2017/04/30 18:33:34 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

/*
**op_31_select(table id: u32, field_cnt: u8, fields: u8[]) -> SelectResponse
**	Return a u32 result count, followed by as many results.
**	If field_cnt is 0, all fields are sent.
**
**	typedef struct	s_tbl_head
**	{
**		uint32_t	id;
**		uint32_t	len;
**	
**		uint32_t	next_id;
**		uint32_t	entry_size;
**	
**		uint32_t	bd_blk;
**		uint16_t	hd_blk;
**	
**		uint8_t		label[33];
**	
**		uint8_t		field_len;
**		t_field		field;
**	}				t_tbl_head;
**
**	typedef struct	s_req31
**	{
**		uint32_t	tid;
**		uint32_t	limit;
**		uint8_t		field_len;
**		uint8_t		cmp_len;
**		uint8_t		order_len;
**	
**		uint8_t		field[255];
**		uint8_t		*tab_start;
**	}				t_req31;
*/

#define FIELD req->field[i]
#define FIELD_SIZE(F) (F->len * F->size)

t_field		*field(t_tab_head *tab, uint8_t fid)
{
	if (fid >= tab->schema_len)
	{
		ERROR("FIELD ID OUT OF BOUNDS");
		return (NULL);
	}
	return ((t_field*)(tab + 1) + fid);
}

uint32_t	calc_field_offset(t_tbl_head *tab, uint8_t index)
{
	t_field		*current;
	uint32_t	offset;
	uint8_t		i;

	i = 0;
	offset = 0;
	while (i < index)
	{
		current = field(tab, i);
		offset += FIELD_SIZE(current);
		i++;
	}
	return (offset);
}

static int	write_fields(int sock, t_tbl_head *tab, t_req31 *req)
{
	t_field		*current;
	uint32_t	i;

	i = 0;
	while (i < req->field_len)
	{
		if (!(current = field(tab, FIELD)))
			return (1);
		if (FIELD != 0 && req->offset[FIELD] == 0)
			req->offset[FIELD] = calc_field_offset(tab, FIELD);
		write(sock, entr + req->offset[FIELD],
				FIELD_SIZE(current));
		i++;
	}
	return (0);
}

static int	write_selction(int sock, t_tbl_head *tab, t_req31 *req,
		uint32_t *offsets)
{
	uint8_t		*entry;
	uint32_t	i;
	uint32_t	entry_count

	entry_count = (tab->len < req.limit ? tab->len : req->limit);
	write(sock, &entry_count, sizeof(entry_count));
	i = 0;
	req->entry = (U8*)req.tab_start;
	while (i < tab->len && entry_count-- > 0)
	{
		if (*(U32*)(req->entry))
		{
			if (write_fields(sock, tab, req))
				return (1);
			i++;
		}
		req->entr += tab->entry_size;
	}
	return (0);
}

/*
** returns [x,y,z] entries from fields
*/

void	op_31_select(int sock)
{
	t_req31		req;
	t_tbl_head	*tab;
	uint32_t	entry_count;


	if (!sy_read(sock, &req, 11))
	{
		ERROR("ERROR READING SOCKET");
		return ;
	}
	bzero(req.offset, sizeof(req.offset));
	db_rlock();
	tab = table(req.tid); 
	req.tab_start = TAB_DB(tab);
	if (write_selection(sock, tab, &req, field_offsets) == 1)
		ERROR("SELECTION ERROR");
	db_unlock();
}
