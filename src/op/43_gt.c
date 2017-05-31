/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   43_gt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 15:21:23 by iwordes           #+#    #+#             */
/*   Updated: 2017/05/30 16:13:30 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syph.h>

#define RNG_F(T) (T >= 0x10 && T <= 0x1f)
#define RNG_I(T) (T >= 0x04 && T <= 0x07)
#define RNG_U(T) (T >= 0x00 && T <= 0x03)

/*
** NOTE: There's probably a more DRY way to do this.
*/

static bool	cmp_s(t_field *meta, U8 *lhs, U8 *rhs)
{
	if (meta->type == SYT_F64)
		return (*(f64_t*)lhs > *(f64_t*)rhs);
	else if (meta->type == SYT_F32)
		return (*(f32_t*)lhs > *(f32_t*)rhs);
	else if (meta->type == SYT_I64)
		return (*(i64_t*)lhs > *(i64_t*)rhs);
	else if (meta->type == SYT_I32)
		return (*(i32_t*)lhs > *(i32_t*)rhs);
	else if (meta->type == SYT_I16)
		return (*(i16_t*)lhs > *(i16_t*)rhs);
	else
		return (*(i8_t*)lhs > *(i8_t*)rhs);
}

static bool	cmp_u(t_field *meta, U8 *lhs, U8 *rhs)
{
	if (meta->type == SYT_U64)
		return (*(u64_t*)lhs > *(u64_t*)rhs);
	else if (meta->type == SYT_U32)
		return (*(u32_t*)lhs > *(u32_t*)rhs);
	else if (meta->type == SYT_U16)
		return (*(u16_t*)lhs > *(u16_t*)rhs);
	else
		return (*(u8_t*)lhs > *(u8_t*)rhs);
}

static bool	cmp_1(t_field *meta, U8 *lhs, U8 *rhs)
{
	if (RNG_F(meta->type) || RNG_I(meta->type))
		return cmp_s(meta, lhs, rhs);
	if (RNG_U(meta->type))
		return cmp_u(meta, lhs, rhs);

	lprintf("[%.8s] \e[93mWarning\e[0m: > not implemented: %.2x\n",
			sy_time(), meta->type);
	return (false);
}

#define LHS lhs + i * meta->size
#define RHS rhs + i * meta->size

bool	op_43_gt(t_field *meta, U8 *lhs, U8 *rhs)
{
	if (meta->type == SYT_UTF8)
		return (strncmp((char*)lhs, (char*)rhs, meta->len) > 0);
	for (uint32_t i = 0; i < meta->len; i += 1)
		if (!cmp_1(meta, LHS, RHS))
			return (false);
	return (true);
}
