/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:07:16 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/30 22:51:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*return_tab(int tab, int *new_i)
{
	if (tab == 0)
		return (*new_i += 2, ft_strdup("''"));
	else
		return (*new_i += 2, ft_strdup(""));
}

void	ft_substr_mini_2(char *line, t_minishell **mini, int *len)
{
	while (line[*len] && line[*len] != ' ' && line[*len] != '<'
		&& line[*len] != '>' && line[*len] != '|')
	{
		if (line[*len] == SGL_Q || line[*len] == DBL_Q)
		{
			valid_quotes(line[(*len)++], &((*mini)->sgl_q), &((*mini)->dbl_q));
			while ((line[*len] && (*mini)->sgl_q && line[*len] != SGL_Q)
				|| (line[*len] && (*mini)->dbl_q && line[*len] != DBL_Q))
				(*len)++;
			valid_quotes(line[(*len)++], &((*mini)->sgl_q), &((*mini)->dbl_q));
		}
		while (line[*len] && line[*len] != SGL_Q && line[*len] != DBL_Q
			&& line[*len] != ' ' && line[*len] != '<' && line[*len] != '>'
			&& line[*len] != '|')
			(*len)++;
	}
}

char	*get_cmd(char **av, int i)
{
	char	*cmd;

	if (!av || !av[i])
		return (NULL);
	cmd = ft_strdup(av[i++]);
	while (av[i] || str_multi_cmp(av[i], ">", ">>", "<", "<<", "|"))
		cmd = ft_strjoin_n_free(ft_strjoin_n_free(cmd, " ", 1), av[i++], 1);
	return (cmd);
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
