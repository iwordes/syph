/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 12:13:51 by kdavis            #+#    #+#             */
/*   Updated: 2017/04/30 17:49:47 by kdavis           ###   ########.fr       */
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

#define FIELD req->field[j]
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

static int	write_selction(int sock, t_tbl_head *tab, t_req31 *req,
		uint32_t offsets)
{
	t_field		*current;
	uint32_t	entr;
	uint32_t	j;
	uint32_t	entry_count

	entry_count = (tab->len < req.limit ? tab->len : req->limit);
	write(sock, &entry_count, sizeof(entry_count));
	entr = 0;
	while (entr < tab->bd_blk && entry_count-- > 0)
	{
		j = ~0;
		if (*(U32*)(req.tab_start + entr))
			while (++j < req->field_len)
			{
				if (!(current = field(tab, FIELD)))
					return (1);
				if (FIELD != 0 && field_offsets[FIELD] == 0)
					offsets[FIELD] = calc_field_offset(tab, FIELD);
				write(sock, req.tab_start + entr + offsets[FIELD],
						FIELD_SIZE(current));
			}
		entr += tab->entry_size;
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
	uint32_t	field_offsets[255];
	uint32_t	entry_count;


	if (!sy_read(sock, &req, 11))
	//	error;

	bzero(field_offsets, sizeof(field_offsets));
	db_rlock();
	tab = table(req.tid); 
	req.tab_start = TAB_DB(tab);
	if (write_selection(sock, tab, &req, field_offsets) == 1)
		ERROR("SELECTION ERROR");
	db_unlock();
}
