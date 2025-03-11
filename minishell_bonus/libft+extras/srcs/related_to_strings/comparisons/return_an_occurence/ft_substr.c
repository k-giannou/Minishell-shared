/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:32:21 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/09 16:54:23 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* returns a new string that started at start, and end at len or the end of s.
	If start is greater than the lenght of s or if s doesn't exist, it returns
	an empty string
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int				i;
	char			*new_str;
	unsigned int	limit;

	if (start >= ft_strlen(s) || !s[0])
	{
		new_str = malloc(1);
		if (!new_str)
			return (NULL);
		new_str[0] = '\0';
		return (new_str);
	}
	limit = start + (unsigned int)len;
	if (limit > ft_strlen(s))
		len = ft_strlen(s) - start;
	new_str = malloc(len + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while ((size_t)start < limit && s[start])
		new_str[i++] = s[start++];
	new_str[i] = '\0';
	return (new_str);
}

/* #include <stdio.h>
#include <string.h>

int	main(void)
{
	char *str = "01234";
	size_t size = 10;
	char *ret = ft_substr(str, 10, size);


	printf("%s\n", ret);
	if (!strncmp(ret, "", 1))
	{
		free(ret);
		printf("nickel");
		return (0);
	}
	free(ret);
	return (0);
} */
