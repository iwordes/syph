/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 10:25:04 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/03 11:09:43 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

/*
** Look up a field in a table schema by index.
*/

t_field	*tab_field(t_tab *tab, U8 id)
{
	return (tab->schema[id % tab->schema_len]);
}
