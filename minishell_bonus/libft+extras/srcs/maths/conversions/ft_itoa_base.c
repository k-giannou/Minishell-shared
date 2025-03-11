/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:31:07 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/09 16:56:02 by locagnio         ###   ########.fr       */
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

static int	init_vals(long nb, int *sign, char *base)
{
	int	i;
	int	digits;

	i = 0;
	digits = 1;
	if (nb < 0)
	{
		nb = -nb;
		*sign = 1;
	}
	while (nb >= (int)ft_strlen(base))
	{
		nb /= (int)ft_strlen(base);
		digits++;
	}
	i = digits + *sign;
	return (i);
}

/* turn a number into a string in a certain base
*/
char	*ft_itoa_base(int n, char *base)
{
	char	*cpy;
	long	nb;
	int		i;
	int		sign;

	ft_error(base);
	nb = n;
	sign = 0;
	i = init_vals(nb, &sign, base);
	if (nb < 0)
		nb = -nb;
	cpy = malloc(sizeof(char) * i + 1);
	if (!cpy)
		return (NULL);
	if (sign == 1)
		cpy[0] = '-';
	cpy[i--] = '\0';
	while (i >= sign)
	{
		cpy[i] = base[nb % (int)ft_strlen(base)];
		nb /= (int)ft_strlen(base);
		i--;
	}
	return (cpy);
}

/* #include <stdio.h>
#include <string.h>

int	main(void)
{
	printf("nombre attendu : 0\n\tretour : %s\n\n", ft_itoa_base(0,\
	 "0123456789ABCDEF"));
	printf("nombre attendu : 9\n\tretour : %s\n\n", ft_itoa_base(9,\
	 "0123456789ABCDEF"));
	printf("nombre attendu : -9\n\tretour : %s\n\n", ft_itoa_base(-9,\
	 "0123456789ABCDEF"));
	printf("nombre attendu : D\n\tretour : %s\n\n", ft_itoa_base(13,\
	 "0123456789ABCDEF"));
	printf("nombre attendu : -F\n\tretour : %s\n\n", ft_itoa_base(-15,\
	 "0123456789ABCDEF"));
	printf("nombre attendu : 1FBC\n\tretour : %s\n\n", ft_itoa_base(8124,\
	 "0123456789ABCDEF"));
	return (0);
} */