/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:32:27 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/09 16:56:20 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

static void	error_msg(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

static int	ft_error(char *base)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if ((int)ft_strlen(base) <= 1)
		error_msg(RED"Error : invalid base\n"RESET);
	if (base[i] == ' ' || base[i] == '-' || base[i] == '+'
		|| (base[i] >= 9 && base[i] <= 13))
		error_msg(RED"Error : white spaces in base\n"RESET);
	while (i <= (int)ft_strlen(base))
	{
		while (j <= (int)ft_strlen(base))
		{
			if (base[i] == base[j])
				error_msg(RED"Error : duplicates in base\n"RESET);
			if (base[j] == ' ' || base[j] == '-' || base[j] == '+'
				|| (base[j] >= 9 && base[j] <= 13))
				error_msg(RED"Error : white spaces in base\n"RESET);
			j++;
		}
		i++;
		j = i + 1;
	}
	return (0);
}

/* turn a decimal string into an int in a certain base
*/
int	ft_atoi_base(const char *nptr, char *base)
{
	int		i;
	int		sign;
	long	result;
	int		len_base;

	i = 0;
	sign = 1;
	result = 0;
	len_base = (int)ft_strlen(base);
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (!ft_error(base) && (nptr[i] == '-' || nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nptr[i] >= base[0] && nptr[i] <= base[len_base - 1])
	{
		result = result * len_base + ft_strclen(base, nptr[i]);
		i++;
	}
	if (result * sign > 2147483647 || result * sign < -2147483648)
		error_msg(RED"Error : result bigger than int in atoi base\n"RESET);
	return ((int)result * sign);
}

/* #include <stdio.h>

int	main(void)
{
	printf("nombre attendu : 0\n\tretour : %d\n\n", ft_atoi_base("0", "01"));
	printf("nombre attendu : 9\n\tretour : %d\n\n", ft_atoi_base("1001", "01"));
	printf("nombre attendu : -9\n\tretour : %d\n\n", ft_atoi_base(\
	"-1001", "01"));
	printf("nombre attendu : 13\n\tretour : %d\n\n", ft_atoi_base(\
	"1101", "01"));
	printf("nombre attendu : -15\n\tretour : %d\n\n", ft_atoi_base(\
	"-1111", "01"));
	printf("nombre attendu : 8124\n\tretour : %d\n\n", ft_atoi_base(\
	"1111110111100", "01"));
	return (0);
} */