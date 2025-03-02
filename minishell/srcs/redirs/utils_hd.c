/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_hd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiannou <kgiannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 10:48:12 by kgiannou          #+#    #+#             */
/*   Updated: 2025/03/02 19:00:01 by kgiannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	heredoc (char **tokens, char **pipes_redirs)
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

void	free_strs(char **str1, char **str2, char **str3)
{
	if (*str1)
	{
		free(*str1);
		*str1 = NULL;
	}
	if (*str2)
	{
		free(*str2);
		*str2 = NULL;
	}
	if (*str3)
	{
		free(*str3);
		*str3 = NULL;
	}
}

int	hd_filename(char **tokens, char ** pipes_redirs)
{
	int	y;
	
	y = 0;
	while (tokens[y])
	{
		if (pipes_redirs[y])
		{
			if (!ft_strcmp(tokens[y], "<<"))//check if exist eof at least one time
			{	
				if (tokens[y + 1])
					return (1);
					//return (ft_fprintf(2, "bash: syntax error near unexpected token `newline'\n"), 0);		
			}
		}
		y++;
	}
	return (0);
}
void	correct_null_tabs(int size_tokens, char **tokens, char **pipes_redirs)
{
	int	y;
	int	i;
	char	*tmp;

	y = 0;
	i = 0;
	while (i < size_tokens)//correct null tabs between tokens because we free eof words, same at redirs
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
				return (ft_fprintf(2, "bash: syntax error near unexpected token `%s'\n", pipes_redirs[i + 1]), 1);
			break ;
		}
		else if (pipes_redirs[i] && pipes_redirs[i + 1])
			// if (syntax_error_redir(tokens, pipes_redirs))
				return (ft_fprintf(2, "bash: syntax error near unexpected token `%s'\n", pipes_redirs[i + 1]), 1);

		i++;
	}
	return (0);
}
