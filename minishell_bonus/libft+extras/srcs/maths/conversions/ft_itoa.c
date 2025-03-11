/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:31:07 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/09 16:55:59 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

static int	init_vals(long nb, int *sign)
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
	while (nb >= 10)
	{
		nb /= 10;
		digits++;
	}
	i = digits + *sign;
	return (i);
}

/* turn a number into an string
*/
char	*ft_itoa(int n)
{
	char	*cpy;
	long	nb;
	int		i;
	int		sign;

	nb = n;
	sign = 0;
	i = init_vals(nb, &sign);
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
		cpy[i] = nb % 10 + '0';
		nb /= 10;
		i--;
	}
	return (cpy);
}

/* #include <stdio.h>
#include <string.h>

int	main(void)
{
	char *i1 = ft_itoa(0);
	char *i2 = ft_itoa(9);
	char *i3 = ft_itoa(-9);
	char *i4 = ft_itoa(10);
	char *i5 = ft_itoa(-10);
	char *i6 = ft_itoa(8124);

	if (strcmp(i1, "0"))
	{
		printf("la reponse attendue : 0\nma reponse : %s\n", i1);
		printf("fail test 1");
		return (0);
	}
	if (strcmp(i2, "9"))
	{
		printf("la reponse attendue : 9\nma reponse : %s\n", i2);
		printf("fail test 2");
		return (0);
	}
	if (strcmp("-9", i3))
	{
		printf("la reponse attendue : -9\nma reponse : %s\n", i3);
		printf("fail test 3");
		return (0);
	}
	if (strcmp(i4, "10"))
	{
		printf("la reponse attendue : 10\nma reponse : %s\n", i4);
		printf("fail test 1");
		return (0);
	}
	if (strcmp(i5, "-10"))
	{
		printf("la reponse attendue : -10\nma reponse : %s\n", i5);
		printf("fail test 2");
		return (0);
	}
	if (strcmp("8124", i6))
	{
		printf("la reponse attendue : 8124\nma reponse : %s\n", i6);
		printf("fail test 3");
		return (0);
	}
	printf("gg win");
	return (0);

} */