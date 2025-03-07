/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:33:50 by locagnio          #+#    #+#             */
/*   Updated: 2025/01/17 18:08:53 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* Concatenates 2 strings and guarantee to NUL-terminate the result if dsize
	is at least greater than the len of dst. Both src and dst must be
	NUL-terminated. It returns the final len of the concatenated string */

size_t	ft_strlcat(char *dst, const char *src, size_t dsize)
{
	unsigned int	i;
	unsigned int	len_trunc;
	unsigned int	len_dest;

	i = 0;
	len_dest = ft_strlen(dst);
	if (dsize <= len_dest)
		return (dsize + ft_strlen(src));
	len_trunc = ft_strlen(dst) + ft_strlen(src);
	while (src[i] != '\0' && i < dsize - len_dest - 1)
	{
		dst[len_dest + i] = src[i];
		i++;
	}
	dst[len_dest + i] = '\0';
	return (len_trunc);
}

/* #include <stdio.h>
#include <string.h>

int	main(void)
{
	char dest1[100] = "Hello ";
	char src[] = "World";
	unsigned int size = 8;

	printf("%zu\n", ft_strlcat(dest1, src, size));
	puts(dest1);
	return (0);
} */