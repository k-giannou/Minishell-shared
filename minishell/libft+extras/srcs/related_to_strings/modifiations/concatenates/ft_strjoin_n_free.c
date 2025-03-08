/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_n_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:07:25 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/08 17:21:39 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* join 2 strings and free whatever used string you want to free :
	- 1 : free s1
	- 2 : free s2
	- 12 : free both s1 and s2 */
char	*ft_strjoin_n_free(char *s1, char *s2, int tab_to_free)
{
	char	*new_string;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	new_string = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, 1);
	if (!new_string)
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		new_string[i] = s1[i];
		i++;
	}
	while (s2 && s2[j] != '\0')
		new_string[i++] = s2[j++];
	new_string[i] = '\0';
	if (tab_to_free == 1)
		free(s1);
	else if (tab_to_free == 2)
		free(s2);
	else if (tab_to_free == 12)
		return (free(s1), free(s2), new_string);
	return (new_string);
}
