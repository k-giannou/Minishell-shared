/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:07:16 by locagnio          #+#    #+#             */
/*   Updated: 2025/04/04 19:00:15 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redir_if_needed(char **env, t_minishell *mini)
{
	int		sig;
	char	**split;
	char	**redirs;

	sig = 0;
	split = NULL;
	redirs = NULL;
	if (mini->cmd_s_redirs[mini->p.i])
	{
		split = ft_splitdup(mini->cmd_s[mini->p.i]);
		redirs = get_redir_split(mini, mini->p.i);
		sig = redir(mini, env, split, redirs);
		free_pipes_redirs(redirs, ft_count_words((const char **)split));
		free_dbl_tab(split);
	}
	return (sig);
}
