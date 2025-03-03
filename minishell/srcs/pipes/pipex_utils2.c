/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:14:22 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/03 22:19:42 by marvin           ###   ########.fr       */
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
	return (ft_splitndup(mini->pipes_redirs,
			ft_count_words(mini->tokens), start, *j));
}

int	isredir_pipex(char *tokens)
{
	int	i;

	i = 0;
	while (tokens && tokens[i])
	{
		if (tokens[i] == '<' || tokens[i] == '>')
			return (1);
		i++;
	}
	return (0);
}

void	create_pipes(t_pipes *pipes_struct)
{
	int	i;

	i = 0;
	pipes_struct->pipes = malloc(sizeof(int *) * pipes_struct->nb_pipes);
	if (!pipes_struct->pipes)
		return ((void)ft_fprintf(2, RED"Error : fail initiate pipes\n"RESET));
	while (i < pipes_struct->nb_pipes)
	{
		pipes_struct->pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(pipes_struct->pipes[i]) == -1)
			return (free_pipes(pipes_struct->pipes, pipes_struct->nb_pipes),
				(void)ft_fprintf(2, RED"Error : fail initiate pipes\n"RESET));
		i++;
	}
}

void	close_and_redirect_pipes(t_pipes *pipes_struct, int current_pipe)
{
	int	i;

	i = 0;
	while (pipes_struct->pipes && i < pipes_struct->nb_pipes)
	{
		if (i == current_pipe)
		{
			close(pipes_struct->pipes[i][0]);
			dup2(pipes_struct->pipes[i][1], STDOUT_FILENO);
			close(pipes_struct->pipes[i][1]);
		}
		else if (current_pipe != 0 && i == current_pipe - 1)
		{
			close(pipes_struct->pipes[i][1]);
			dup2(pipes_struct->pipes[i][0], STDIN_FILENO);
			close(pipes_struct->pipes[i][0]);
		}
		else
		{
			close(pipes_struct->pipes[i][0]);
			close(pipes_struct->pipes[i][1]);
		}
		i++;
	}
}

void	close_all_pipes(t_pipes *pipes_struct, int current_pipe)
{
	int	i;

	if (!pipes_struct->pipes)
		return ;
	i = 0;
	while (i < pipes_struct->nb_pipes && i < current_pipe - 1)
	{
		close(pipes_struct->pipes[i][0]);
		close(pipes_struct->pipes[i][1]);
		i++;
	}
	if (i == current_pipe - 1)
		close(pipes_struct->pipes[i][1]);
}
