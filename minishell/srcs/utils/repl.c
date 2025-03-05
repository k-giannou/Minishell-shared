/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:25:54 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/05 15:39:13 by locagnio         ###   ########.fr       */
=======
/*   By: kgiannou <kgiannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:25:54 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/05 15:35:34 by kgiannou         ###   ########.fr       */
>>>>>>> 75fd9508efe331307b8f832369f89961c15a5834
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	search_and_change(t_variables *v, char *str, t_minishell *mini,
		t_env *current)
{
	char	*dest;

	current = mini->env;
	v->i++;
	v->t = 0;
	current = mini->env;
	while (ft_isalpha(str[v->i]) || ft_isdigit(str[v->i]) || str[v->i] == '_')
		v->to_search[v->t++] = str[v->i++];
	v->to_search[v->t++] = '\0';
	dest = ft_strdup(v->to_search);
	while (current)
	{
		if (ft_strncmp(dest, current->data, ft_strlen(dest)) == 0)
		{
			while (current->data[v->t] != '\0')
				v->line[v->k++] = current->data[v->t++];
			break ;
		}
		current = current->next;
	}
	free(dest);
	dest = NULL;
}

void	start_replace(t_variables *v, char *str, t_minishell *mini,
		t_env *current)
{
	char	*num;
	int		i;

	while (str[v->i] != '\0')
	{
		if (str[v->i] == '\'' && (!v->dbl_quote))
			handle_single(v, str);
		else if (str[v->i] == '\"')
			change_bools(v, str);
		else if (str[v->i] == '$')
		{
			if (str[v->i + 1] == '\0' || str[v->i + 1] == 32 || str[v->i
					+ 1] == '$')
				v->line[v->k++] = str[v->i++];
			else if (str[v->i + 1] == '?')
			{
				v->i += 2;
				num = ft_itoa(g_signal);
				i = 0;
				while (num[i])
					v->line[v->k++] = num[i++];
				free (num);
				num = NULL;
			}
			else if (str[v->i + 1] == '\"' && v->dbl_quote)
				v->line[v->k++] = str[v->i++];
			else if ((str[v->i + 1] == '\"' || str[v->i + 1] == '\'')
				&& (!v->dbl_quote))
				v->i++;
			else if (ft_isalpha(str[v->i + 1]) || ft_isdigit(str[v->i + 1])
				|| str[v->i + 1] == '_')
				search_and_change(v, str, mini, current);
			else
				v->line[v->k++] = str[v->i++];
		}
		else
			v->line[v->k++] = str[v->i++];
	}
}

char	*replace_var(t_minishell *mini, char *str)
{
	t_env		*current;
	t_variables	v;

	if (!str)
		return (ft_exit(mini), NULL);
	v = (t_variables){0};
	v = mini->vars;
	current = mini->env;
	if (!current)
		return (NULL);
	else
		start_replace(&v, str, mini, current);
	v.line[v.k] = '\0';
	free(str);
	return (ft_strdup(v.line));
}
