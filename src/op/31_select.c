/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 12:13:51 by kdavis            #+#    #+#             */
/*   Updated: 2017/04/29 14:37:23 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

static void	select_init(t_req31 *request)
{
	tp_rlock(&g_mn.db.lock);
	DBE_READ(read(sock, &request->tid, sizeof(request->tid)));
	DBE_READ(read(sock, &request->field_count, sizeof(request->field_count)));
	DBE_READ(read(sock, request->fields, request->field_count));
	tp_rwunlock();
}

/*
**op_31_select(table id: u32, field_cnt: u8, fields: u8[]) -> SelectResponse
**	Return a u32 result count, followed by as many results.
**	If field_cnt is 0, all fields are sent.
*/

void	op_31_select(int sock)
{
	t_req31		input;
	uint32_t	result_count;
	t_field		*current;

	bzero(input, sizeof(input));
	select_init(fields);

	/*
	** Do some stuff to select the appropriate output
	** get result_count
	**
	** tp_wlock(&g_mn.db.lock);
	** for (int i = 0; i < result_count; i++)
	** {
	**		
	** }
	*/

}
