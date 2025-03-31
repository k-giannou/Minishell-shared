/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitndup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:33:46 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/31 18:24:22 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* create a dublicate of a splited string at start tab up to end tab
*/
char	**ft_splitndup(char **split, int len_split, int start, int end)
{
	char	**dup;
	int		i;
	int		len;

	if (end > len_split)
		end = len_split;
	if (start >= end || !split)
		return (NULL);
	len = end - start + 1;
	dup = (char **)malloc(sizeof(char *) * len);
	if (!dup)
		return (NULL);
	i = 0;
	while (start < end)
		dup[i++] = ft_strdup(split[start++]);
	dup[i] = NULL;
	return (dup);
}
