/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiannou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:55:21 by kgiannou          #+#    #+#             */
/*   Updated: 2025/02/07 19:55:32 by kgiannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char  *replace_var(t_minishell *mini, char *str)//str=$user
{
        t_env     *current;
	
        current = mini->env;
        if (!current)
			return NULL;
		while (current)
        {
				if (ft_strncmp(str, current->data, strlen(str)) == 0)
				{		
					//printf("%s\n", current->data + (strlen(str) + 1));
					return (current->data + (strlen(str) + 1));
				}
                current = current->next;
        }
		return (str);
}
