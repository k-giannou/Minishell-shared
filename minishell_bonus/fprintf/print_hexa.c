/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 20:46:57 by locagnio          #+#    #+#             */
/*   Updated: 2025/01/31 17:54:16 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	ft_len_hexa(unsigned int nb, t_struct *v)
{
	int	len_hexa;

	len_hexa = 1;
	while (nb >= 16)
	{
		nb /= 16;
		len_hexa++;
	}
	v->nb1 -= len_hexa;
	if (srch_flag(v->flags, '.') && v->nb2 > len_hexa)
	{
		v->zeros = v->nb2 - len_hexa;
		len_hexa += v->zeros;
	}
	if (srch_flag(v->flags, '#'))
		len_hexa += 2;
	return (len_hexa);
}

void	print_hexa_if_no_0(t_struct v, int len_hexa, unsigned int nb, int i)
{
	v.nb1 -= len_hexa;
	if (!srch_flag(v.flags, '-'))
		while (v.nb1-- > 0)
			write(v.fd, " ", 1);
	hexa_print(nb, v, v.str[i]);
	if (srch_flag(v.flags, '-'))
		while (v.nb1-- > 0)
			write(v.fd, " ", 1);
}

int	reset_len_hexa(int len_hexa, t_struct v)
{
	len_hexa -= v.zeros;
	if (srch_flag(v.flags, '#'))
		len_hexa -= 2;
	return (len_hexa);
}

void	ft_print_hexa(unsigned int nb, t_struct v, int i, int *count)
{
	int	len_hexa;

	if (nb == 0)
	{
		ft_print_int(0, v, count);
		return ;
	}
	len_hexa = ft_len_hexa(nb, &v);
	*count += len_hexa;
	len_hexa -= reset_len_hexa(len_hexa, v);
	if (v.nb1 > len_hexa)
	{
		*count += v.nb1 - len_hexa;
		if (srch_flag(v.flags, '0') && !srch_flag(v.flags, '.'))
		{
			if (v.nb1 > len_hexa)
				v.zeros += v.nb1 - len_hexa;
			hexa_print(nb, v, v.str[i]);
		}
		else
			print_hexa_if_no_0(v, len_hexa, nb, i);
	}
	else
		hexa_print(nb, v, v.str[i]);
}
