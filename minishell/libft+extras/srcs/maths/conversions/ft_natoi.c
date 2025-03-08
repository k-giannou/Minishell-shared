/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_natoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:23:02 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/08 17:30:57 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* turn every numbers contained in a string separated with white spaces into a
	list of numbers */
int	ft_natoi(const char *nptr, int *i)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while (nptr[*i] == ' ' || (nptr[*i] >= 9 && nptr[*i] <= 13))
		*i += 1;
	if (nptr[*i] == '-' || nptr[*i] == '+')
	{
		if (nptr[*i] == '-')
			sign = -sign;
		*i += 1;
	}
	while (nptr[*i] >= '0' && nptr[*i] <= '9')
	{
		result = result * 10 + nptr[*i] - '0';
		*i += 1;
	}
	return (result * sign);
}
