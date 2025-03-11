/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:32:27 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/09 16:56:25 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

static double	decimal(char *nptr)
{
	int		i;
	int		divizor;
	double	result;

	i = 0;
	divizor = 10;
	result = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result + (double)(nptr[i] - '0') / divizor;
		divizor *= 10;
		i++;
	}
	return (result);
}

/* turn a decimal number string into an double
*/
double	ft_atod(char *nptr)
{
	int		i;
	int		sign;
	double	result;

	if (!nptr)
		return (0);
	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - '0';
		i++;
	}
	if (nptr[i] == '.' || nptr[i] == ',')
		result += decimal(nptr + i + 1);
	return (result * sign);
}

/* #include <stdio.h>

int	main(void)
{
	const char nptr[] = "   +1234ab567";

	printf("%d\n", ft_atoi(nptr));
	return(0);

} */