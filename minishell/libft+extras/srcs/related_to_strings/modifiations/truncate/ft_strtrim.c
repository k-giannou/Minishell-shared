/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:32:16 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/09 16:52:35 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

static int	set_cmp(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/* return a new string by removing the characters found in "set" string at start
	and end	of s1
*/
char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	j;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s1);
	while (set_cmp(s1[i], set))
		i++;
	if (i == j)
		return (ft_strdup(""));
	j--;
	while (set_cmp(s1[j], set) && j > i)
		j--;
	return (ft_substr(s1, i, j - i + 1));
}

/* #include <stdio.h>
#include <string.h>

int	main(void)
{
	char *s1 = "   \t  \n\n \t\t  \n\n \t  \n \n	\n \n \t\t\n  ";
	char *s2 = "";
	char *ret = ft_strtrim(s1, " \n\t");

	printf("%s\n", ret);
	if (!strcmp(ret, s2))
		printf("nickel");
	free(ret);
	return (0);
} */
