/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitjoin_n_free.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:26:24 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/13 16:37:07 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* join 2 splits and free whatever used split you want to free :
	- 1 : free s1
	- 2 : free s2
	- 12 : free both s1 and s2
*/
char	**ft_splitjoin_n_free(char **s1, char **s2, int tab_to_free)
{
	char	**new_split;
	size_t	len;
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	len = ft_count_words((const char **)s1) +
		ft_count_words((const char **)s2) + 1;
	new_split = malloc(len);
	if (!new_split)
		return (NULL);
	while (s1[++i])
		new_split[i] = ft_strdup(s1[i]);
	while (s2[j])
		new_split[i++] = ft_strdup(s2[j++]);
	new_split[i] = NULL;
	if (tab_to_free == 1)
		free_dbl_tab(s1);
	else if (tab_to_free == 2)
		free_dbl_tab(s2);
	else if (tab_to_free == 12)
		return (free_dbl_tab(s1), free_dbl_tab(s2), new_split);
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