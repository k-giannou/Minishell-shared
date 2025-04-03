/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:07:16 by locagnio          #+#    #+#             */
/*   Updated: 2025/04/03 20:13:29 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	pipe_count(t_btree *the_tree)
{
	int	i;
	int	count;
	int	len_split;

	i = 0;
	count = 0;
	len_split = ft_count_words((const char **)the_tree->tokens);
	while (i < len_split)
	{
		if (the_tree->pipes_redirs[i]
			&& !ft_strncmp(the_tree->pipes_redirs[i], "|", 1))
			count++;
		i++;
	}
	return (count);
}

int	get_sig(int status)
{
	int	sig;

	sig = 0;
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status) + 128;
		if (sig == 141)
			sig = 0;
		else if (sig == 131)
			ft_fprintf(2, "Quit (code dumped)\n");
		return (sig);
	}
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (ft_fprintf(2, "minishell : error : Fail getting the signal "),
			ft_fprintf(2, "of last cmd\n"));
}

int	isredir_str(char *str)
{
	if (!str)
		return (0);
	if (ft_strchr(str, '>') || ft_strchr(str, '<')
		|| ft_strsrch(str, ">>") || ft_strsrch(str, "<<"))
		return (1);
	return (0);
}
