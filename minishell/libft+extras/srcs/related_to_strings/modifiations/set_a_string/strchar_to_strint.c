/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchar_to_strint.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiannou <kgiannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:46:21 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/21 13:24:41 by kgiannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

static bool	correct_format(char *str_char)
{
	int	i;

	i = 0;
	while (str_char[i])
	{
		if (ft_isnum(str_char[i]) || str_char[i] == '-' || str_char[i] == '+')
			i++;
		else if (ft_strcmp(str_char + i, ", ") && i != 0)
			i += 2;
		else
			return (0);
	}
	return (1);
}

/*	convert a string of char to a string of int.

	- The string must follow the format : "n1, n2, ..., nn".
	- If the format isn't respected, or if the string is NULL or empty, the
	function returns NULL
*/
int	*strchar_to_strint(char *str_char)
{
	int	i;
	int	j;
	int	*str_int;

	if (!str_char || !str_char[0] || !correct_format(str_char))
		return (NULL);
	str_int = malloc(sizeof(int) * ft_strintlen(str_char));
	i = 0;
	j = 0;
	while (str_char[i])
	{
		if (str_char[i] != ',')
			str_int[j++] = ft_natoi(str_char, &i);
		else
			i++;
	}
	return (str_int);
}
