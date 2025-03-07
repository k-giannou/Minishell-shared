/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:32:32 by locagnio          #+#    #+#             */
/*   Updated: 2025/01/17 17:35:16 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* set whatever argument to zero */

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char *)(s + i) = 0;
		i++;
	}
}

/* #include <stdio.h>

int	main(void)
{
	void *tab;
	int i = 0;

	tab = malloc(sizeof(char) * 13);
	if (!tab)
		return (0);
	ft_bzero(tab, 5);
	while (i < 5)
		printf("%c\n", *(char *)(tab + i++) + 48);
	return (0);
} */