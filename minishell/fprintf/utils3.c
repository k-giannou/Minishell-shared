/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:08:53 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/25 18:34:22 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	ft_putnbr_base_f(unsigned int nbr, char *base, int fd)
{
	if (nbr >= 16)
		ft_putnbr_base_f(nbr / 16, base, fd);
	write(fd, &base[nbr % 16], 1);
}

void	hexa_print(unsigned int nb, t_struct v, char x)
{
	char	*str;

	if (x == 'x' && srch_flag(v.flags, '#'))
		write(v.fd, "0x", 2);
	else if (x == 'X' && srch_flag(v.flags, '#'))
		write(v.fd, "0X", 2);
	while (v.zeros-- > 0)
		write(v.fd, "0", 1);
	if (x == 'x')
		str = "0123456789abcdef";
	else
		str = "0123456789ABCDEF";
	ft_putnbr_base_f(nb, str, v.fd);
}

int	ft_digits(long n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while (n >= 10)
	{
		n /= 10;
		count++;
	}
	return (count);
}
