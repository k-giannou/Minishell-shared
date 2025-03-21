/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiannou <kgiannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:33:46 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/21 12:40:46 by kgiannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* create a dublicate of a splited string
*/
char	**ft_splitdup(char **split)
{
	char	**dup;
	int		i;

	if (!split)
		return (NULL);
	dup = (char **)malloc(sizeof(char *) * \
			(ft_count_words((const char **)split) + 1));
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

/* #include <stdio.h>

int	main(void)
{
	char src[] = "Hello";
	char *cpy;

	cpy = ft_strdup(src);
	printf("adresse de src : %p\nsrc : %s\nadresse de cpy : %p\ncpy : %s\n",\
	src, src, cpy, cpy);
	free (cpy);
	return (0);
} */