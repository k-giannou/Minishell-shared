/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:33:46 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/03 22:22:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

char	**ft_splitdup(char **split)
{
	char	**dup;
	int		i;

	if (!split)
		return (NULL);
	dup = (char **)malloc(sizeof(char *) * (ft_count_words(split) + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (split[i])
	{
		dup[i] = ft_strdup(split[i]);
		if (!dup[i])
			return (free_dbl_tab(dup), NULL);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
