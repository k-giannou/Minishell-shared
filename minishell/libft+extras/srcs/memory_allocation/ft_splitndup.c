/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitndup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:33:46 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/09 16:55:17 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* create a dublicate of a splited string at start tab up to end tab
*/
char	**ft_splitndup(char **split, int len_split, int start, int end)
{
	char	**dup;
	int		i;

	if (end > len_split)
		end = len_split;
	if (start > end || !split)
		return (NULL);
	dup = (char **)malloc(sizeof(char *) * (end - start + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (start < end)
		dup[i++] = split[start++];
	dup[i] = NULL;
	return (dup);
}
