/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 20:09:37 by locagnio          #+#    #+#             */
/*   Updated: 2025/01/18 16:08:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* copy n bytes of a fixed string to another fixed string */

char	*ft_strncat(char *dest, char *src, size_t nb)
{
	int		i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < nb)
		dest[i++] = src[j++];
	dest[i] = '\0';
	return (dest);
}

/*int main(void)
{
	char dest[] = "Hello ";
	char src[] = "World";
	unsigned int nb = 7;

	printf("%s\n", ft_strncat(dest, src, nb));
	return (0);
}*/