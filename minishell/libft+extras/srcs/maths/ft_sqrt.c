/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:36:44 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/08 17:30:42 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* return the square root of a number */
int	ft_sqrt(int nb)
{
	int	i;

	i = 0;
	if (nb <= 0)
		return (0);
	while (++i <= nb / 2)
		if (i * i == nb)
			return (i);
	return (0);
}

/*int main(void)
{
	printf("%d\n", ft_sqrt(16));
	return (0);
}*/
