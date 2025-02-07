/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 20:01:18 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/07 20:17:56 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_var(t_minishell *mini, char *str)//str=$user
{
	t_env	*current;
	char	*dest;
	int	len;
	int	i;

	current = mini->env;
	if (!current)
		return NULL;
	len = 0;
	i = 0;
	while (current)
	{
		if (ft_strncmp(str, current->data, strlen(str)) == 0)
		{
			len = strlen(current->data);
			len = len - strlen(str) + 1;
			dest = malloc(sizeof(char)* len + 1);
			if (!dest)
				return (NULL);
			len = strlen(str) + 1;
			while(current->data[i + len] != '\0')
			{
				dest[i] = current->data[i + len];
				i++;
			}
					
			//printf("%s\n", dest);
			return (dest);
		}
		current = current->next;
	}
	return (str);
}