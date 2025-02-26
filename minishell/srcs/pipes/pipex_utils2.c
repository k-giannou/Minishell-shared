/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:14:22 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/26 21:35:51 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_redir_split(t_minishell *mini, int *j)
{
	int	start;

	if (!mini->pipes_redirs || !mini->tokens)
		return (NULL);
	start = *j;
	while (mini->pipes_redirs[*j] && !ft_strcmp(mini->pipes_redirs[*j], "|"))
		(*j)++;
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
