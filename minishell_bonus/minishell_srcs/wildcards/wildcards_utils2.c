/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiannou <kgiannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:32:54 by kgiannou          #+#    #+#             */
/*   Updated: 2025/04/07 16:44:19 by kgiannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_fnmatch_rec(const char *pattern, const char *str, int *i)
{
	int	result1;
	int	result2;

	while (*pattern == '*' && (*(pattern + 1) ==  '*'))
		pattern++;
	while (*pattern == '\"')
	{
		(*i)++;
		pattern++;
	}
	if (*pattern == '\0')
		return (*str == '\0');
	if (*pattern == '*' && (*i % 2 != 0))
	{
		result1 = ft_fnmatch_rec(pattern + 1, str, i);
		result2 = 0;
		if (*str != '\0')
			result2 = ft_fnmatch_rec(pattern, str + 1, i);
		return (result1 || result2);
	}
	if (*pattern == *str)
		return (ft_fnmatch_rec(pattern + 1, str + 1, i));
	return (0);
}

bool	handle_pattern(struct dirent *entry,
char *pattern, DIR *dp, t_variables *v)
{
	int		i;
	bool	found;

	found = false;
	while (entry != NULL)
	{
		i = 1;
		if (entry->d_name[0] != '.'
			&& ft_fnmatch_rec(pattern, entry->d_name, &i))
		{
			replace_file_in_str(v, entry->d_name);
			found = true;
		}
		entry = readdir(dp);
	}
	return (found);
}

int	search_for_patterns(char *pattern, t_variables *v)
{
	int				i;
	struct dirent	*entry;
	DIR				*dp;
	bool			found;

	dp = opendir(".");
	if (dp == NULL)
		return (perror("opendir"), 0);
	(void)v;
	entry = readdir(dp);
	found = handle_pattern(entry, pattern, dp, v);
	closedir(dp);
	if (found)
	{
		i = 0;
		while (pattern[i++])
			v->i++;
		return (1);
	}
	return (0);
}

int	process_pattern(t_variables *v, char *str)
{
	v->found = false;
	v->point = wildcars_exist_at(str, v->i, false);
	if (v->point == -1)
		return (0);
	v->i_start = find_start(str, v->point);
	v->i_end = find_end(str, v->point);
	if (v->i_start == -1 || v->i_end == -1)
	{
		printf("fail to find start/end of *\n");
		return (0);
	}
	return (1);
}
