/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 12:13:51 by kdavis            #+#    #+#             */
/*   Updated: 2017/04/29 21:17:41 by kdavis           ###   ########.fr       */
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
**	}				t_req31;
*/

#define FIELD req.field[i]
#define FIELD_SIZE(F) (F->len * F->size)

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

void	op_31_select(int sock)
{
	t_req31		req;
	t_tbl_head	*tab;
	t_field		*current;
	uint32_t	field_offsets[255];
	size_t		i;


	if (!sy_read(sock, &req, 11))
	//	error;

	bzero(field_offsets, sizeof(field_offsets));
	db_rlock();
	tab = table(req.tid); 
	req.tab_start = TAB_DB(tab);
	i = 0;
	write(sock, &req.field_len, sizeof(req.field_len));
	while (i < req.field_len)
	{
		current = field(tab, FIELD);
		if (FIELD != 0 && field_offsets[FIELD] == 0)
			field_offsets[FIELD] = calc_field_offset(tab, FIELD);
		write(sock, req.tab_start + field_offsets[FIELD], FIELD_SIZE(current));
		i++;
	}
	db_unlock();
}
