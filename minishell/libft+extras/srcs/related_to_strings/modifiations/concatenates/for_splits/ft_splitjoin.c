/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:26:24 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/13 17:28:19 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* creates a new split by concatenate 2 splits
*/
char	**ft_splitjoin(char const **s1, char const **s2)
{
	char	**new_split;
	size_t	len;
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	len = ft_count_words(s1) + ft_count_words(s2) + 1;
	new_split = malloc(len);
	if (!new_split)
		return (NULL);
	while (s1[++i])
		new_split[i] = ft_strdup(s1[i]);
	while (s2[j])
		new_split[i++] = ft_strdup(s2[j++]);
	new_split[i] = NULL;
	return (new_split);
}

/* #include <stdio.h>

int	main(void)
{
	char *s1 = "Hello ";
	char *s2 = "World";

	s1 = ft_strjoin(s1, s2);
	printf("%s\n", s1);
	free(s1);
	return (0);
} */