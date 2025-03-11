/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:33:59 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/09 16:54:02 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* returns the len of as string when :
	- it reaches the first iteration of c
	- it reaches the end of the string
*/
size_t	ft_strclen(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s && s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

/* #include <stdio.h>

int	main(void)
{
	char str[] = "Yeppi";

	printf("%zu\n", ft_strlen(str));
	return(0);
} */
