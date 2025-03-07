/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiannou <kgiannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:57:59 by kgiannou          #+#    #+#             */
/*   Updated: 2025/03/07 21:19:12 by kgiannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_fnmatch_rec(const char *pattern, const char *str)
{
	static int	i;

	if (*pattern == '\"')
	{
		i++;
		pattern++;
	}
	if (*pattern == '\0')
        return *str == '\0';
	if (*pattern == '*' && (i % 2 != 0))
	{
		int	result1 = ft_fnmatch_rec(pattern + 1, str);
		int	result2 = 0;
		if (*str != '\0')
			result2 = ft_fnmatch_rec(pattern, str + 1);
		return (result1 || result2);
	}
	if (*pattern == *str)
		return (ft_fnmatch_rec(pattern + 1, str + 1));
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

// void	search_test(void)
// {
// 		if (ft_fnmatch_rec("\"*\"fi*le", "*file"))
// 			printf("match\n");
// 		else
// 			printf("no file\n");
// }

int	search_for_patterns(char *pattern, t_variables *v)
{
	(void)v;
	struct dirent *entry;
	DIR *dp = opendir(".");
	bool	found;

	found = false;
	if (dp == NULL)
		return (perror("opendir"), 0);
	while ((entry = readdir(dp)) != NULL)
	{
		if (entry->d_name[0] != '.' && ft_fnmatch_rec(pattern, entry->d_name))
		{
			replace_file_in_str(v, entry->d_name);
			found = true;
		}
	}
	closedir(dp);
	if (found)
	{
		int i = 0;
		while (pattern[i++])
			v->i++;
		return (1);
	}
	return (0);
}

char	*handle_wildcards(char *str, t_minishell *mini)
{
	t_variables	v;
	int	i_start;
	int	i_end;
	int	point;
	bool	found;

	v = (t_variables){0};
	v = mini->vars;
	v.i = 0;
	v.dbl_quote = false;
	while (str[v.i] != '\0')
	{
		found = false;
		point = wildcars_exist_at(str, v.i, false);
		if (point == -1)
			break ;
		//printf("point = %d\n", point);
		i_start = find_start(str, point);
		if (i_start == -1)
		{				
			printf("error in finding start of *\n");
			break ;
		}
		//printf("start = %d = %c\n", i_start, str[i_start]);
		
		i_end = find_end(str, point);
		if (i_end == -1)
		{
			printf("error in finding end of *\n");
			break ;
		}
		// printf("end = %d = %c\n", i_end, str[i_end]);
		
		while (v.i < i_start)//copy untill --i_start, before change it
			v.line[v.k++] = str[v.i++];
		
		int s = 0;
		while (i_start <= i_end)
			v.to_search[s++] = str[i_start++];
		v.to_search[s] = '\0';
		char *pattern = ft_strdup(v.to_search);
		//printf("patternt = %s\n", pattern);
		if (search_for_patterns(pattern, &v))
		{
			v.dbl_quote = true;
			found = true;
		}
		//if i dont find files for the pattern, i copy until the i_end.
		//if i find files, i have lalready change the v.i
		free (pattern);
		pattern = NULL;
		if (!found)
		{
			while (v.i <= i_end)
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