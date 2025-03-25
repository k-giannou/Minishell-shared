/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_signed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:01:22 by locagnio          #+#    #+#             */
/*   Updated: 2025/01/31 17:54:21 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	ft_len_nb(long nb, t_struct *v)
{
	int	len_nb;
	int	sign;

	len_nb = 0;
	sign = 0;
	if (nb == 0 && srch_flag(v->flags, '.') && v->nb2 == 0)
		return (0);
	if (nb < 0)
	{
		nb = -nb;
		sign = 1;
		len_nb++;
	}
	len_nb += ft_digits(nb);
	if ((srch_flag(v->flags, ' ') || srch_flag(v->flags, '+')) && sign != 1)
	{
		len_nb++;
		sign++;
	}
	if (srch_flag(v->flags, '.') && v->nb2 > len_nb - sign)
	{
		v->zeros = v->nb2 - (len_nb - sign);
		len_nb += v->zeros;
	}
	return (len_nb);
}

void	print_nb_if_no_0(t_struct v, int len_nb, long nb)
{
	v.nb1 -= len_nb;
	if (!srch_flag(v.flags, '-'))
		while (v.nb1-- > 0)
			write(v.fd, " ", 1);
	ft_putnbr(nb, v, 10, 0);
	if (srch_flag(v.flags, '-'))
		while (v.nb1-- > 0)
			write(v.fd, " ", 1);
}

void	ft_print_int(long nb, t_struct v, int *count)
{
	int	len_nb;

	len_nb = ft_len_nb(nb, &v);
	*count += len_nb;
	if (v.nb1 > len_nb)
	{
		*count += v.nb1 - len_nb;
		if (srch_flag(v.flags, '0') && !srch_flag(v.flags, '.'))
		{
			v.zeros += v.nb1 - len_nb;
			ft_putnbr(nb, v, 10, 0);
		}
		else
			print_nb_if_no_0(v, len_nb, nb);
	}
	else
		ft_putnbr(nb, v, 10, 0);
}
