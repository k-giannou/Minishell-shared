/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:26:24 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/12 17:33:03 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* creates a new string by concatenate n characters of 2 strings */

char	*ft_strnjoin(char const *s1, size_t n_s1, char const *s2, size_t n_s2)
{
	char	*new_string;
	size_t	len;
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	if (n_s1 > ft_strlen(s1))
		n_s1 = ft_strlen(s1);
	if (n_s2 > ft_strlen(s2))
		n_s2 = ft_strlen(s2);
	len = n_s1 + n_s2 + 1;
	new_string = malloc(len);
	if (!new_string)
		return (NULL);
	while (s1[++i] != '\0' && i < n_s1)
		new_string[i] = s1[i];
	while (s2[j] != '\0' && j < n_s2)
		new_string[i++] = s2[j++];
	new_string[i] = '\0';
	return (new_string);
}

/* #include <stdio.h>

int	main(void)
{
	char *s1 = "Hello ";
	char *s2 = "World";

	s1 = ft_strjoin(s1, s2);
	printf("%s\n", s1);
	free(s1);
	return (0);
} */