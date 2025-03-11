/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:09:44 by marvin            #+#    #+#             */
/*   Updated: 2025/01/18 16:09:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

static void	error_msg(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

int	ft_error(char *base)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if ((int)ft_strlen(base) <= 1)
		error_msg(RED"Error : Invalid base\n"RESET);
	while (i <= (int)ft_strlen(base))
	{
		while (j <= (int)ft_strlen(base))
		{
			if (base[i] == base[j] || base[i] == '-'
				|| base[i] == '+' || base[j] == '-'
				|| base[j] == '+')
				error_msg(RED"Error : signs or duplicates in base\n"RESET);
			j++;
		}
		i++;
		j = i + 1;
	}
	return (1);
}

/* write an int into the base chosen
*/
void	ft_putnbr_base(int nbr, char *base)
{
	long	nb;
	int		len_base;

	nb = nbr;
	len_base = (int)ft_strlen(base);
	if (ft_error(base))
	{
		if (nb < 0)
		{
			write(1, "-", 1);
			nb = -nb;
		}
		if (nb >= len_base)
			ft_putnbr_base(nb / len_base, base);
		write(1, &base[nb % len_base], 1);
	}
}
