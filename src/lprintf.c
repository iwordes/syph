/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lprintf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 23:07:38 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/05 11:02:40 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>
#include <stdarg.h>

#pragma clang diagnostic ignored "-Wformat-nonliteral"

int		lprintf(const char *msg, ...)
{
	va_list	ap;
	int		o;

	va_start(ap, msg);
	tp_mlock(&g_mn.llock);
	o = vdprintf(g_mn.log, msg, ap);
	tp_munlock(&g_mn.llock);
	va_end(ap);
	return (o);
}
