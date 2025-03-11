/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:33:07 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/09 16:54:34 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* scans n bytes of a string for the first instance of c and return the rest of
	the string where c was found
*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)(s + i) == (unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	return (0);
}

/* #include <stdio.h>

int	main(void)
{
	const char *tab = "Hello world";
	int c = 'o';
	const void *s = tab;

	s = ft_memchr(s, c, 3);
	printf("%s\n", (unsigned char *)s);
	return(0);
} */
