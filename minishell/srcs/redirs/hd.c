/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiannou <kgiannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:12:44 by kgiannou          #+#    #+#             */
/*   Updated: 2025/03/01 18:06:05 by kgiannou         ###   ########.fr       */
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

void	copy_eofs(int *sum, char **eofs, char **tokens, char **pipes_redirs)
{
	int	y;
	int	i;

	y = 0;
	i = 0;
	while (tokens[y] && tokens[y + 1])
	{
		if (pipes_redirs[y] && !ft_strcmp(pipes_redirs[y], "<<") 
			&& !pipes_redirs[y + 1] && tokens[y + 1])//if next is null it means there is a name eof so we take it
			{
				eofs[i] = ft_strdup(tokens[y + 1]);
				if (!eofs[i])
					return (free_dbl_tab(eofs));
				free_strs(&pipes_redirs[y], &tokens[y], &tokens[y + 1]);//free the symbol <<, symbol << from tokens, eof worlds from tokens
				if (i++ < *sum - 1)//need to delete  << eof if its not he last-one
					y++;
				else//keep the last and put symbol <
				{
					pipes_redirs[y] = ft_strdup("<");//put <
					tokens[y] = ft_strdup("<");//put <
					tokens[y++ + 1] = ft_strdup(".heredoc.txt");//put file name
				}	
			}
		y++;
	}
	eofs[i] = NULL;
}

char	**find_eofs(int *sum, char **tokens, char **pipes_redirs)
{
	int	y;
	char	**eofs;
	
	if (!tokens)
		return (NULL);
	y = 0;
	while (tokens[y] && tokens[y + 1])
	{
		if (pipes_redirs[y] && !ft_strcmp(pipes_redirs[y], "<<"))
		{
			// if (ft_strcmp(tokens[y + 1], ">") || ft_strcmp(tokens[y + 1], ">>")
			// 	|| ft_strcmp(tokens[y + 1], "<") || ft_strcmp(tokens[y + 1], "<<")
			// 	|| ft_strcmp(tokens[y + 1], "<>"))
			if (!pipes_redirs[y + 1])
					(*sum)++;
		}
		y++;
	}
	if (sum == 0)
		return (NULL);
	eofs = (char **)malloc(sizeof(char*) * (*sum + 1));
	if (!eofs)
		return (NULL);
	copy_eofs(sum, eofs, tokens, pipes_redirs);
	return (eofs);
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

int	create_heredoc(char **eofs)
{
	int	fd;
	char	*line;
	int	y;
	int	first;
	
	first = 0;
	fd = open(".heredoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
	{
		ft_fprintf(2, "Bash: heredoc.txt");
		perror(":");
		return (0);
	}
	ft_fprintf(0, ">");
	line = get_next_line(STDIN_FILENO);
	y = 0;
	while (line)
	{
		if (ft_strncmp(line, eofs[y], ft_strlen(eofs[y])) == 0
			&& line[ft_strlen(eofs[y])] == '\n')
		{
			y++;
			if (y == ft_count_words(eofs))//when it founds the last eof
			{
				free (line);
				break ;
			}
		}
		ft_fprintf(0, ">");
		if (y == ft_count_words(eofs) - 1)//write only between last and pre-last
		{
				first++;
				if (first != 1)
					write(fd, line, ft_strlen(line));
		}
		free(line);
		line = NULL;
		line = get_next_line(STDIN_FILENO);
	}
	return (1);
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

int	handle_heredoc (char **tokens, char **pipes_redirs)
{
	bool	error;
	char	**eofs;
	int	sum;
	int	size_tokens;

	if (!tokens)
		return (0);
	size_tokens = ft_count_words(tokens);
	sum = 0;
	error = false;
	if (!hd_filename(tokens, pipes_redirs))
		return (ft_fprintf(2, "bash: syntax error near unexpected token `newline'\n"), 0);
	if (syntax_error_before_hd(tokens, pipes_redirs))
		return (0);
	if (syntax_error_redir(tokens, pipes_redirs))
		error = true;
	eofs = find_eofs(&sum, tokens, pipes_redirs);
	if (!eofs)
		return (0);
	if (!create_heredoc(eofs))
		return (free_dbl_tab(eofs), 0);
	correct_null_tabs(size_tokens, tokens, pipes_redirs);
	ft_print_dlb_tabs(tokens, "tokens after");
	print_pipes_redirs(pipes_redirs, size_tokens);
	if (!error && !valid_filename(tokens, pipes_redirs))
		error = true;
	if (error)
		return (free_dbl_tab(eofs), 0);
	else
		return (free_dbl_tab(eofs), 1);
}

