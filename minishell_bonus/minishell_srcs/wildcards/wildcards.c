/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiannou <kgiannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:57:59 by kgiannou          #+#    #+#             */
/*   Updated: 2025/03/24 12:39:53 by kgiannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_var_wild(t_variables *v, t_minishell *mini)
{
	*v = mini->vars;
	*v = (t_variables){0};
	v->i = 0;
	v->dbl_quote = false;
}

void	handle_if_not_found(t_variables *v, char *str)
{
	if (!v->found)
	{
		while (v->i <= v->i_end)
			v->line[v->k++] = str[v->i++];
	}
}

char	*final_str(t_variables *v, char *str)
{
	while (str[v->i] != '\0')
		v->line[v->k++] = str[v->i++];
	v->line[v->k] = '\0';
	free (str);
	str = NULL;
	return (ft_strdup(v->line));
}

void	set_bools_found(char *pattern, t_variables *v)
{
	if (search_for_patterns(pattern, v))
	{
		v->dbl_quote = true;
		v->found = true;
	}
}

char	*handle_wildcards(char *str, t_minishell *mini)
{
	t_variables	v;
	char		*pattern;

	init_var_wild(&v, mini);
	while (str[v.i] != '\0')
	{
		if (!process_pattern(&v, str))
			break ;
		while (v.i < v.i_start)
			v.line[v.k++] = str[v.i++];
		v.s = 0;
		while (v.i_start <= v.i_end)
			v.to_search[v.s++] = str[v.i_start++];
		v.to_search[v.s] = '\0';
		pattern = ft_strdup(v.to_search);
		set_bools_found(pattern, &v);
		free (pattern);
		pattern = NULL;
		handle_if_not_found(&v, str);
	}
	if (!v.dbl_quote)
		return (str);
	return (final_str(&v, str));
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