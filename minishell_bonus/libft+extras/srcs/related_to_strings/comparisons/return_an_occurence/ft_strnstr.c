/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:34:10 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/09 16:54:27 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* search for the first iteration of little string into len bytes of big string
	and returns the rest of big string at the first iteration found. If little
	is null, the function returns big
*/
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*little)
		return ((char *)big);
	i = 0;
	j = 0;
	while (i < len && big[i])
	{
		while (big[i + j] == little[j] && (i + j) < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)big + i);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

/* #include <stdio.h>

char	*strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*needle)
		return ((char *)haystack);
	i = 0;
	while (i < len && haystack[i] != '\0')
	{
		j = 0;
		while (haystack[i + j] == needle[j] && (i + j) < len)
		{
			if (needle[j + 1] == '\0')
			{
				return (char *)(haystack + i);
			}
			++j;
		}
		++i;
	}
	return (NULL);
}

int	main(void)
{
	const size_t size = 20;
	char *s1 = "is there a nyacat ?";
	char *s2 = "is there a nyacat ?";

	char *i1 = strnstr(s1, s1, size);
	char *i2 = ft_strnstr(s1, ((void*)0), size);

	printf("original : %s\nreplique : %s\n", i1, i2);
	if (i1 == i2)
		printf("c'est bon");
	return (0);
} */