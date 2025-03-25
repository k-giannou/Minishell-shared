/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:48:01 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/01 13:02:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	ft_null_ptr(t_struct v, int *count)
{
	char	*nil;

	nil = "(nil)";
	if (v.nb1 - 5 > 0 && !ft_strcmp(nil, "(nil)"))
	{
		if (v.nb1 >= 5)
			*count += v.nb1 - 5;
		if (srch_flag(v.flags, '-'))
			ft_putstr(nil, count, 5, v.fd);
		v.nb1 -= 5;
		while (v.nb1-- > 0)
			write(v.fd, " ", 1);
		if (!srch_flag(v.flags, '-'))
			ft_putstr(nil, count, 5, v.fd);
	}
	else
		ft_putstr(nil, count, 5, v.fd);
}

int	ft_len_ptr(size_t ptr, t_struct *v)
{
	int	len_ptr;

	len_ptr = 1;
	while (ptr >= 16)
	{
		ptr /= 16;
		len_ptr++;
	}
	len_ptr += (int)ft_strlen("0x");
	if (srch_flag(v->flags, '.') && v->nb2 > len_ptr - 2)
	{
		v->zeros = v->nb2 - (len_ptr - 2);
		len_ptr += v->zeros;
	}
	if (srch_flag(v->flags, ' ') || srch_flag(v->flags, '+'))
		len_ptr++;
	return (len_ptr);
}

void	print_ptr_if_no_0(t_struct v, int len_ptr, size_t ptr)
{
	v.nb1 -= len_ptr;
	if (!srch_flag(v.flags, '-'))
		while (v.nb1-- > 0)
			write(v.fd, " ", 1);
	ptr_print(ptr, v);
	if (srch_flag(v.flags, '-'))
		while (v.nb1-- > 0)
			write(v.fd, " ", 1);
}

void	ft_print_ptr(size_t ptr, t_struct v, int *count)
{
	int	len_ptr;

	if (!ptr)
	{
		ft_null_ptr(v, count);
		return ;
	}
	len_ptr = ft_len_ptr(ptr, &v);
	*count += len_ptr;
	if (v.nb1 > len_ptr)
	{
		*count += v.nb1 - len_ptr;
		if (srch_flag(v.flags, '0'))
		{
			v.zeros += v.nb1 - len_ptr;
			ptr_print(ptr, v);
		}
		else
			print_ptr_if_no_0(v, len_ptr, ptr);
	}
	else
		ptr_print(ptr, v);
}
