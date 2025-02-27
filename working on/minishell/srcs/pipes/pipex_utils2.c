/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:14:22 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/27 16:43:14 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_redir_split(t_minishell *mini, int *j, int len_split)
{
	int	start;

	if (!mini->pipes_redirs || !mini->tokens)
		return (NULL);
	start = *j;
	while (*j < len_split && ft_strcmp(mini->pipes_redirs[*j], "|"))
		(*j)++;
	if (!ft_strcmp(mini->pipes_redirs[*j], "|"))
		(*j)--;
	return (ft_splitndup(mini->pipes_redirs, ft_count_words(mini->tokens), start, *j));
}

int	isredir_pipex(char *tokens)
{
	int	i;

	i = 0;
	while(tokens && tokens[i])
	{
		if (tokens[i] == '<' || tokens[i] == '>')
			return (1);
		i++;
	}
	return (0);
}
