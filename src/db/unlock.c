/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlock.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 14:16:01 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/22 14:17:38 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	db_unlock(t_db *db)
{
	tp_rwunlock(&db->lock);
}
