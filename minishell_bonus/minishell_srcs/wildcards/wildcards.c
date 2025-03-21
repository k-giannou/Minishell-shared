/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiannou <kgiannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:57:59 by kgiannou          #+#    #+#             */
/*   Updated: 2025/03/21 13:58:16 by kgiannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_fnmatch_rec(const char *pattern, const char *str, int *i)
{
	int	result1;
	int	result2;

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

void	replace_file_in_str(t_variables *v, char *file)
{
	int	i;

	i = 0;
	while (file[i] != '\0')
		v->line[v->k++] = file[i++];
	v->line[v->k++] = 32;
}

int	search_for_patterns(char *pattern, t_variables *v)
{
	int				i;
	struct dirent	*entry;
	DIR				*dp;
	bool			found;

	dp = opendir(".");
	i = 1;
	(void)v;
	found = false;
	if (dp == NULL)
		return (perror("opendir"), 0);
	entry = readdir(dp);
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

char	*handle_wildcards(char *str, t_minishell *mini)
{
	t_variables	v;
	char		*pattern;

	v = mini->vars;
	v = (t_variables){0};
	v.i = 0;
	v.dbl_quote = false;
	while (str[v.i] != '\0')
	{
		v.found = false;
		v.point = wildcars_exist_at(str, v.i, false);
		if (v.point == -1)
			break ;
		v.i_start = find_start(str, v.point);
		if (v.i_start == -1)
		{
			printf("error in finding start of *\n");
			break ;
		}
		v.i_end = find_end(str, v.point);
		if (v.i_end == -1)
		{
			printf("error in finding end of *\n");
			break ;
		}
		while (v.i < v.i_start)
			v.line[v.k++] = str[v.i++];
		v.s = 0;
		while (v.i_start <= v.i_end)
			v.to_search[v.s++] = str[v.i_start++];
		v.to_search[v.s] = '\0';
		pattern = ft_strdup(v.to_search);
		if (search_for_patterns(pattern, &v))
		{
			v.dbl_quote = true;
			v.found = true;
		}
		free (pattern);
		pattern = NULL;
		if (!v.found)
		{
			while (v.i <= v.i_end)
				v.line[v.k++] = str[v.i++];
		}
	}
	if (!v.dbl_quote)
		return (str);
	while (str[v.i] != '\0')
		v.line[v.k++] = str[v.i++];
	v.line[v.k] = '\0';
	free (str);
	return (ft_strdup(v.line));
}
/*

// void	search_test(void)
// {
// 		if (ft_fnmatch_rec("\"*\"fi*le", "*file"))
// 			printf("match\n");
// 		else
// 			printf("no file\n");
// }


*/