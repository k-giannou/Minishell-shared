/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:33:35 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/09 16:52:54 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* set n bytes of s with c
*/
void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char *)(s + i) = (char)c;
		i++;
	}
	return (s);
}

/* #include <stdio.h>

int	main(void)
{
	void *s = malloc(30);
	int c = 49;

	s = ft_memset(s, c, 30);
	printf("%s\n", (char *)s);
	return (0);
} */
