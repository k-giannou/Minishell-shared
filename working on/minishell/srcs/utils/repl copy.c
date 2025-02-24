/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl copy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:14:36 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/10 16:56:07 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* int	ft_isalnum(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9'))
		return (1);
	return (0);
}

char	*ft_strcat(char *dest, char *src)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
		dest[i++] = src[j++];
	dest[i] = '\0';
	return (dest);
}

char	*is_valid_env(char *str, t_minishell *mini)
{
	int i;
	char env[50];
	t_env *mini_env;

	i = -1;
	while (++i < 50)//set to zero
		env[i] = 0;
	env[0] = '$';//first is a dollar
	i = 0;
	while (str[++i] && (ft_isalnum(str[i]) || str[i] == '_'))//while i have letters or underscore
		env[i] = str[i];//i copy
	mini_env = mini->env;
	while (mini_env)
	{
		if (!ft_strncmp(env + 1, mini_env->data, ft_strlen(env) - 2))//if i found a env
			return (ft_strdup(mini_env->data +
				ft_strclen(mini_env->data, '=') + 1));//i send the matching data
		mini_env = mini_env->next;
	}
	return (0);
}

void	put_env(char *line, char *str, t_minishell *mini, int *i)
{
	char *env_var;

	env_var = is_valid_env(str + (*i)++, mini);
	if (env_var != NULL)
		ft_strcat(line, env_var);//i cat and ajust i to len of var found
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))//then i skip everything that was connected to the $
		(*i)++;
	free(env_var);
}

char    *replace_var(t_minishell *mini, char *str)
{
	char	line[100000];
	char	*env_var;
	int		i;
	int		j;
	
	if (str && str[0] == 0)
		return (free(str), ft_strdup(""));//if empty string
	i = -1;
	while (++i < 100000)//set to zero
		line[i] = 0;
	env_var = NULL;
	i = -1;
	j = 0;
	while (str && str[++i])
	{
		if (str[i] == SGL_Q || str[i] == DBL_Q)//if quotes
			valid_quotes(str[i], &(mini->sgl_q), &(mini->dbl_q));//set one open or closed
		if (str[i] == '$' && ft_isalnum(str[i + 1]) && mini->sgl_q == 0)//if i have a dollar followed by a letter and it's not in an open single quote
			put_env(line, str, mini, &i);
		while (line[j])
			j++;
		line[j++] = str[i];
	}
	return (free(str), ft_strdup(line));
} */
