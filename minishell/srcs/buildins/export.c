/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:15:45 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/15 18:24:40 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int 	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	just_export_or_unset(char **vars, char *command)
{
	int	i;

	i = 0;
	while (vars[i])
			i++;
	if (i == 1 && ft_strcmp(vars[i], command) == 0)
		return (1) ;
	return (0);
}

int	first_letter_valid(char *str)
{
	if (ft_isalpha(str[0]) || str[0] == '_')
		return (1);
	return (0);
}

int	rest_letters_of_name(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_' )
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

void    ft_lstadd_back(t_env **lst, t_env *new)
{
    t_env    *temp;

    if (!new)
        return ;
    if (!*lst)
    {
        *lst = new;
        return ;
    }
    temp = *lst;
    while (temp->next)
        temp = temp->next;
    temp->next = new;
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
		return;
	new_node->data = ft_strdup(str);
	new_node->next = NULL;
	ft_lstadd_back(&v, new_node);
}

void	ft_print_export(t_env *v)
{
	bool	sign = false;
	bool	inside = false;
	
	while (v != NULL)
	{
		ft_fprintf (1, "declare -x ");
		int i = 0;
		while (v->data[i])
		{
			if (v->data[i] == '=' && !inside)
			{
				sign = true;
				inside = true;
				ft_fprintf (1, "%c", v->data[i++]);//pass =
				ft_fprintf (1, "\"");
			}
			ft_fprintf (1, "%c", v->data[i++]);
		}
		if (v->data[i] == '\0' && sign)
			ft_fprintf (1, "\"");
		ft_fprintf (1, "\n");
		v = v->next;
		sign = false;
		inside = false;
	}
}
void	export(char **vars, t_minishell *mini)
{
	int	i = 1;
	
	if (just_export_or_unset(vars, "export"))
		return (ft_print_export(mini->env_export));
	else 
		while (vars[i])
		{
			if (!first_letter_valid(vars[i]) || !rest_letters_of_name(vars[i]))
				ft_fprintf(2, "bash: export: `%s': not a valid identifier\n", vars[i]);
			else if (!equal_sign(vars[i]))
				add_in_env(vars[i], mini->env_export);
			else
			{
				add_in_env(vars[i], mini->env);
				add_in_env(vars[i], mini->env_export);
			}
			i++;
		}
	return ;
}
