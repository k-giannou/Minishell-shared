/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:33:27 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/08 17:19:08 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* copies n bytes from src to dest and avoid overlaps */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int	i;
	int	size;

	i = 0;
	size = (int)n;
	if (!dest && !src)
		return (NULL);
	if (dest > src)
	{
		while (--size >= 0)
			*(char *)(dest + size) = *(char *)(src + size);
	}
	else
	{
		while (i < size)
		{
			*(char *)(dest + i) = *(char *)(src + i);
			i++;
		}
	}
	return (dest);
}

/* #include <stdio.h>
#include <string.h>

#define TEST_FAILED ("C'est faux")
#define TEST_SUCCESS ("C'est valide")

int	main(void)
{
	memmove(((void*)0), ((void*)0), 5);
	ft_memmove(((void*)0), ((void*)0), 5);
	printf("original : %s\ncopie : %s\n", (char *)memmove(((void*)0), \
	((void*)0), 5), (char *)ft_memmove(((void*)0), ((void*)0), 5));
	return(0);
} */
/* printf("%s", TEST_SUCCESS);
	printf("%s", TEST_FAILED);
	printf("original : %s\ncopie : %s\n", (char *)memmove(dst1 + 3, dst1, \
	size), (char *)ft_memmove(dst2 + 3, dst2, size)) */
