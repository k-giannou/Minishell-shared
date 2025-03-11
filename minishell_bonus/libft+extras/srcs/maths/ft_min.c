/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:25:29 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/09 16:55:39 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* fint the lowest number of a list
*/
int	ft_min(int *tab)
{
	int	i;
	int	min;

	if (!tab)
		return (404);
	i = 0;
	min = tab[0];
	while (tab[++i])
		if (tab[i] < min)
			min = tab[i];
	return (min);
}
