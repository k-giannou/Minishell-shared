/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:33:11 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/09 16:54:18 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* scans n bytes of 2 strings and return the difference of the 2 strings
*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)(s1 + i) != *(unsigned char *)(s2 + i))
			return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
		i++;
	}
	return (0);
}

/* #include <stdio.h>

int	main(void)
{
	char *s1 = "atoms\0\0\0\0";
	char *s2 = "atoms\0abc";
	size_t size = 8;
	int i1 = ((memcmp(s1, s2, size) > 0) ? 1 : ((memcmp(s1, s2, size) < 0) \
	? -1 : 0));
	int i2 = ((ft_memcmp(s1, s2, size) > 0) ? 1 : ((ft_memcmp(s1, s2, size) \
	< 0) ? -1 : 0));
	printf("i1 : %d\ni2 : %d\n", i1, i2);
	if (i1 == i2)
		printf("c'est bon");
	return (0);
} */