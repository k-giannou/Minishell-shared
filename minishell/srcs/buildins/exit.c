/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:07:06 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/13 20:52:08 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* void	ft_exit(t_minishell *mini, char **line)
{
	char *str;

	str = ft_readline("Are you sure ? [yes/no]\n", mini);
	if (!ft_strcmp("yes", str))
		return (free(str), free_all(mini, line), exit(0));
	else if (!ft_strcmp("no", str))
		ft_fprintf(1, "\nYeh, "UNDERLINE BOLD"you better NOT !"RESET" 😈\n");
	else
		ft_fprintf(1, "\nYou retard sh*t ! 💩\n", mini);
	free(str);
} */

void	ft_exit(t_minishell *mini, char **line)
{
	printf("line : %s", line[0]);
	return (free_all(mini, line), exit(0));
}
