/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:57:10 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/06 17:17:39 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* search for a string into another one at most len bytes */

int	ft_strnchr(const char *s, const char *to_find, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] && i < len)
	{
		while (s[i + j] == to_find[j] && i + j < len)
		{
			j++;
			if (to_find[j] == 0)
				return (1);
		}
		i++;
		j = 0;
	}
	return (0);
}
