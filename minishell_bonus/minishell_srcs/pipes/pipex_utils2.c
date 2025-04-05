/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:14:22 by locagnio          #+#    #+#             */
/*   Updated: 2025/04/05 17:10:00 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//(null) < (null) | (null) (null) > (null) | (null)
// cat   <  file  |  echo   nice  >  file  |  ls

char	**get_redir_split(t_minishell *mini, int cur_cmd)
{
	int	start;
	int	end;
	int	nb_pipe;

	nb_pipe = 0;
	if (!mini->pipes_redirs || !mini->tokens)
		return (NULL);
	start = 0;
	while (nb_pipe < cur_cmd && mini->tokens[start])
	{
		if (!ft_strncmp(mini->tokens[start], "|", 1))
			nb_pipe++;
		start++;
	}
	end = start + 1;
	while (mini->tokens[end] && ft_strncmp(mini->tokens[end], "|", 1))
		end++;
	return (ft_splitndup(mini->pipes_redirs,
			ft_count_words((const char **)mini->tokens), start, end));
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

int	cat_ls(char **cmd_s)
{
	int	i;

	i = ft_count_words((const char **)cmd_s) - 1;
	if (!ft_strcmp(cmd_s[i], "ls"))
	{
		i--;
		while (i >= 0)
		{
			if (i == 0 && !ft_strcmp(cmd_s[i], "cat"))
				break ;
			if (!ft_strcmp(cmd_s[i], "cat"))
				i--;
			else
				break ;
		}
	}
	if (i == 0 && !ft_strcmp(cmd_s[i], "cat"))
		return (1);
	return (0);
}

void	close_curr_pipe(t_pipes *pipes_struct, int current_pipe, char **cmd_s)
{
	if (!pipes_struct->pipes)
		return ;
	(void)cmd_s;
	if (current_pipe < pipes_struct->nb_pipes)
	{
		if (cat_ls(cmd_s))
			close(pipes_struct->pipes[current_pipe][0]);
		close(pipes_struct->pipes[current_pipe][1]);
		if (cat_ls(cmd_s) && current_pipe > 0)
			close(pipes_struct->pipes[current_pipe - 1][0]);
	}
}
