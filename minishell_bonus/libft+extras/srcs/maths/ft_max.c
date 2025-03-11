/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:25:29 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/09 16:55:41 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* fint the highest number of a list
*/
int	ft_max(int *tab)
{
	int	i;
	int	max;

	if (!tab)
		return (404);
	i = 0;
	max = tab[0];
	while (tab[++i])
		if (tab[i] > max)
			max = tab[i];
	return (max);
}
