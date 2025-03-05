/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_hd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiannou <kgiannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 10:48:12 by kgiannou          #+#    #+#             */
/*   Updated: 2025/03/05 15:30:37 by kgiannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	error_in_heredoc(char **tokens, char **pipes_redirs, bool *error)
{
	if (!hd_filename(tokens, pipes_redirs))
		return (ft_fprintf(2,
				"bash: syntax error near unexpected token `newline'\n"), 1);
	if (syntax_error_before_hd(tokens, pipes_redirs))
		return (1);
	if (syntax_error_redir(tokens, pipes_redirs))
		*error = true;
	return (0);
}

int	heredoc(char **tokens, char **pipes_redirs)
{
	int	y;

	y = 0;
	while (tokens[y])
	{
		if (pipes_redirs[y])
		{
			if (!ft_strcmp(pipes_redirs[y], "<<"))
				return (1);
		}
		y++;
	}
	return (0);
}

int	hd_filename(char **tokens, char **pipes_redirs)
{
	int	y;

	y = 0;
	while (tokens[y])
	{
		if (pipes_redirs[y])
		{
			if (!ft_strcmp(tokens[y], "<<"))
			{
				if (tokens[y + 1])
					return (1);
			}
		}
		y++;
	}
	return (0);
}

void	correct_null_tabs(int size_tokens, char **tokens, char **pipes_redirs)
{
	int		y;
	int		i;
	char	*tmp;

	y = 0;
	i = 0;
	while (i < size_tokens)
	{
		if (tokens[i])
		{
			if (i != y)
			{
				tmp = tokens[i];
				tokens[i] = tokens[y];
				tokens[y] = tmp;
				tmp = pipes_redirs[i];
				pipes_redirs[i] = pipes_redirs[y];
				pipes_redirs[y] = tmp;
			}
			y++;
		}
		i++;
	}
}

int	syntax_error_before_hd(char **tokens, char **pipes_redirs)
{
	int	i;

	i = 0;
	while (tokens[i] && tokens[i + 1])
	{
		if (pipes_redirs[i] && !ft_strcmp(pipes_redirs[i], "<<"))
		{
			if (pipes_redirs[i + 1])
				return (ft_fprintf(2,
						"bash: syntax error near unexpected \
						token `%s'\n", pipes_redirs[i + 1]), 1);
			break ;
		}
		else if (pipes_redirs[i] && pipes_redirs[i + 1])
			return (ft_fprintf(2,
					"bash: syntax error near unexpected \
					token `%s'\n", pipes_redirs[i + 1]), 1);
		i++;
	}
	return (0);
}
