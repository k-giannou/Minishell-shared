/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiannou <kgiannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:58:12 by kgiannou          #+#    #+#             */
/*   Updated: 2025/03/24 12:08:45 by kgiannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fnmatch.h>

void	replace_file_in_str(t_variables *v, char *file)
{
	int	i;

	i = 0;
	while (file[i] != '\0')
		v->line[v->k++] = file[i++];
	v->line[v->k++] = 32;
}

int	find_start(char *str, int point)
{
	point--;
	while (point >= 0)
	{
		if (str[point] == '\"')
		{
			point--;
			while (str[point] != '\"' && point >= 0)
				point--;
		}
		if (str[point] == '\'')
		{
			point--;
			while (str[point] != '\'' && point >= 0)
				point--;
		}
		if (ft_iswhitespace(str[point]) || point == 0)
			return (++point);
		point--;
	}
	return (-1);
}

int	find_end(char *str, int point)
{
	point++;
	while (1)
	{
		if (str[point] == '\"')
		{
			point++;
			while (str[point] != '\"' && str[point] != '\0')
				point++;
		}
		if (str[point] == '\'')
		{
			point++;
			while (str[point] != '\'' && str[point] != '\0')
				point++;
		}
		if (ft_iswhitespace(str[point]) || str[point] == '\0')
			return (--point);
		point++;
	}
	return (-1);
}

int	wildcars_exist_at(char *str, int i, bool parse)
{
	while (str[i])
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"' && str[i] != '\0')
				i++;
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i] != '\0')
				i++;
		}
		if (str[i] == '*')
		{
			if (parse)
				return (1);
			return (i);
		}
		i++;
	}
	if (parse)
		return (0);
	return (-1);
}

// int	ft_fnmatch_rec(const char *pattern, const char *str)
// {
// 	if (*pattern == '\0')
//         return *str == '\0';
// 	if (*pattern == '*')
// 	{
// 		int	result1 = ft_fnmatch_rec(pattern + 1, str);
// 		int	result2 = 0;
// 		if (*str != '\0')
// 			result2 = ft_fnmatch_rec(pattern, str + 1);
// 		return (result1 || result2);
// 	}
// 	if (*pattern == *str)
// 		return (ft_fnmatch_rec(pattern + 1, str + 1));
// 	return (0);
// }
