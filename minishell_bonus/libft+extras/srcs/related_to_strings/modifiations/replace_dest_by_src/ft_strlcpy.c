/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:33:55 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/09 16:53:01 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* erase and copy d_size of src in dst, returns the len of src
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t dsize)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if (dsize == 0)
		return (len);
	while (i < dsize - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

/* #include <stdio.h>

int	main(void)
{
	char dst[14];
	char src[] = "Hello World.";

	printf("%zu\n", ft_strlcpy(dst, src, 15));
	printf("%s\n", dst);
	return(0);
} */