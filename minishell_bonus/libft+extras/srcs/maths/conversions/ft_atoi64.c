/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:26:37 by locagnio          #+#    #+#             */
/*   Updated: 2025/04/06 14:24:20 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

static int	error64(const char *str)
{
	printf("bash: exit: %s: numeric argument required\n", str);
	return (-1);
}

static int	cmp_64(char *nptr)
{
	size_t	len_max;
	size_t	len_min;
	int		i;

	i = -1;
	len_max = ft_strlen(INT64_MAX_ATOI);
	len_min = ft_strlen(INT64_MIN_ATOI);
	if ((nptr[0] != '-' && ft_strlen(nptr) > len_max)
		|| (nptr[0] == '-' && ft_strlen(nptr) > len_min))
		return (1);
	else if (nptr[0] != '-' && ft_strlen(nptr) == len_max)
	{
		while (nptr[++i])
			if (nptr[i] > INT64_MAX_ATOI[i])
				return (1);
	}
	else if (nptr[++i] == '-' && ft_strlen(nptr) == len_min)
	{
		while (nptr[++i])
			if (nptr[i] > INT64_MIN_ATOI[i])
				return (1);
	}
	free(nptr);
	return (0);
}

/* turn a string into an int64 (or long long int).
	if the number in the string is out of the limits of int64,
	the program returns -1
*/
int64_t	ft_atoi64(char *nptr)
{
	int		i;
	int		sign;
	int64_t	result;

	i = 0;
	sign = 1;
	result = 0;
	if (cmp_64(ft_remove_from_string(nptr, " \t+", 0)))
		return (error64(nptr));
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		result = result * 10 + nptr[i++] - '0';
	return (result * sign);
}
