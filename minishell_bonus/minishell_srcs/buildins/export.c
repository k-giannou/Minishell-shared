/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:15:45 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/08 21:03:26 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	just_export_or_unset(char **vars, char *command)
{
	int	i;

	i = 0;
	while (vars[i])
		i++;
	if (i == 1 && ft_strcmp(vars[0], command) == 0)
		return (1);
	return (0);
}

int	rest_letters_of_name(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalpha(str[i]) && !ft_isnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	equal_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (str[i + 1] == 32 || str[i + 1] == '\0')
				return (0);
			else
				return (1);
		}
		i++;
	}
	return (0);
}

void	add_in_env(char *str, t_env *v)
{
	t_env	*new_node;
	t_env	*temp;

	temp = v;
	while (temp != NULL)
	{
		if (ft_strncmp(str, temp->data, ft_strclen(str, '=')) == 0)
		{
			free(temp->data);
			temp->data = ft_strdup(str);
			return ;
		}
		temp = temp->next;
	}
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->data = ft_strdup(str);
	new_node->next = NULL;
	ft_list_add_back(&v, new_node);
}

void	export(char **vars, t_minishell *mini)
{
	int	i;

	i = 1;
	if (just_export_or_unset(vars, "export"))
		return (ft_print_export(mini->env_export, false, false));
	while (vars[i])
	{
		if (!first_letter_valid(vars[i]) || !rest_letters_of_name(vars[i]))
			ft_fprintf(2, "minishell: export: `%s': not a valid identifier\n",
				vars[i]);
		else if (!equal_sign(vars[i]))
			add_in_env(vars[i], mini->env_export);
		else
		{
			add_in_env(vars[i], mini->env);
			add_in_env(vars[i], mini->env_export);
		}
		i++;
	}
	ft_env_sort(&mini->env_export);
	mini->cur_loc = replace_by_tilde(mini->env, mini->cur_loc, 1);
	g_signal = 0;
}
