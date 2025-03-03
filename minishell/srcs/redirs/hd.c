/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:12:44 by kgiannou          #+#    #+#             */
/*   Updated: 2025/03/03 22:26:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	copy_eofs(int *sum, char **eofs, char **tokens, char **pipes_redirs)
{
	int	y;
	int	i;

	y = 0;
	i = 0;
	while (tokens[y] && tokens[y + 1])
	{
		if (pipes_redirs[y] && !ft_strcmp(pipes_redirs[y], "<<") && !pipes_redirs[y + 1] && tokens[y + 1])//if next is null it means there is a name eof so we take it
			{
				eofs[i] = ft_strdup(tokens[y + 1]);
				if (!eofs[i])
					return (free_dbl_tab(eofs));
				free_strs(&pipes_redirs[y], &tokens[y], &tokens[y + 1]);//free the symbol <<, symbol << from tokens, eof worlds from tokens
				if (i++ < *sum - 1)//need to delete  << eof if its not he last-one, else keep the last and put symbol <
					y++;
				else
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

int	last_eof(char *line, char **eofs, int *y, int sum)
{
	if (!line || !line[0] 
		|| (!ft_strncmp(line, eofs[*y], ft_strlen(eofs[*y])) && line[ft_strlen(eofs[*y])] == '\n'))
		{
			if (!line || !line[0])
				ft_fprintf(0, "\nbash: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", sum, eofs[*y]);
			(*y)++;
			if (*y == ft_count_words(eofs))//when it founds the last eof
			{
				if (line)
					free(line);
				return (1);
			}
		}
	return (0);	
}

void	write_in_heredoc(int *first, int fd, char *line, char **eofs)
{
	(*first)++;
	if (*first != 1 || ft_count_words(eofs) == 1)
		write(fd, line, ft_strlen(line));
}

int	create_heredoc(char **eofs)
{
	int	fd;
	char	*line;
	int	y;
	int	first;
	int	sum;
	
	first = 0;
	sum = 0;
	fd = open(".heredoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		return (ft_fprintf(2, "Bash: heredoc.txt"), perror(":"), 0);
	y = 0;
	line = NULL;
	while (++sum)
	{	
		ft_fprintf(0, ">");
		line = get_next_line(STDIN_FILENO);//dont forget to correct gnl PUT if read <= 0.
		if (last_eof(line, eofs, &y, sum))
			break ;
		if (y == ft_count_words(eofs) - 1)//write only between last and pre-last
			write_in_heredoc(&first, fd, line, eofs);
		if (line)
			free(line);
		line = NULL;
	}
	return (1);
}

int	error_in_heredoc(char **tokens, char **pipes_redirs, bool *error)
{
	if (!hd_filename(tokens, pipes_redirs))
		return (ft_fprintf(2, "bash: syntax error near unexpected token `newline'\n"), 1);
	if (syntax_error_before_hd(tokens, pipes_redirs))
		return (1);
	if (syntax_error_redir(tokens, pipes_redirs))
		*error = true;
	return (0);
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
	if (error_in_heredoc(tokens, pipes_redirs, &error))
		return (0);
	eofs = find_eofs(&sum, tokens, pipes_redirs);
	if (!eofs || !create_heredoc(eofs))
		return (free_dbl_tab(eofs), 0);
	correct_null_tabs(size_tokens, tokens, pipes_redirs);
	if (!error && !valid_filename(tokens, pipes_redirs))
		error = true;
	if (error)
		return (free_dbl_tab(eofs), 0);
	else
		return (free_dbl_tab(eofs), 1);
}

// ft_print_dlb_tabs(tokens, "tokens after");
// print_pipes_redirs(pipes_redirs, size_tokens);
