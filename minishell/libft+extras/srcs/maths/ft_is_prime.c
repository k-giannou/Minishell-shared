/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 09:58:38 by locagnio          #+#    #+#             */
/*   Updated: 2025/01/18 16:23:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* return true if nb is an prime number */

int	ft_is_prime(int nb)
{
	int	i;

	i = nb / 2 + 1;
	if (nb <= 1)
		return (0);
	while (--i > 1)
		if (nb % i == 0)
			return (0);
	return (1);
}

/*int main(void)
{
	printf("%d\n", ft_is_prime(0));
	return (0);
}*/