/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:12:44 by kgiannou          #+#    #+#             */
/*   Updated: 2025/03/21 17:20:12 by locagnio         ###   ########.fr       */
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
		if (pipes_redirs[y] && !ft_strcmp(pipes_redirs[y], "<<")
			&& !pipes_redirs[y + 1] && tokens[y + 1])
		{
			eofs[i] = ft_strdup(tokens[y + 1]);
			if (!eofs[i])
				return (free_dbl_tab(eofs));
			free_strs(&pipes_redirs[y], &tokens[y], &tokens[y + 1]);
			if (i++ < *sum - 1)
				y++;
			else
				handle_name_hr(pipes_redirs, tokens, y);
		}
		y++;
	}
	eofs[i] = NULL;
}

char	**find_eofs(int *sum, char **tokens, char **pipes_redirs)
{
	int		y;
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
	eofs = (char **)malloc(sizeof(char *) * (*sum + 1));
	if (!eofs)
		return (NULL);
	copy_eofs(sum, eofs, tokens, pipes_redirs);
	return (eofs);
}

int	last_eof(char *line, char **eofs, int *y, int sum)
{
	if (!line || !line[0]
		|| (!ft_strncmp(line, eofs[*y], ft_strlen(eofs[*y]))
			&& line[ft_strlen(eofs[*y])] == '\n'))
	{
		if (!line || !line[0])
			ft_fprintf(0,
				"\nminishell: warning: here-document \
at line %d delimited by end-of-file (wanted `%s')\n",
				sum, eofs[*y]);
		(*y)++;
		if (*y == ft_count_words((const char **)eofs))
		{
			if (line)
				free(line);
			return (1);
		}
	}
	return (0);
}

int	create_heredoc(char **eofs, int sum)
{
	int		fd;
	char	*line;
	int		y;
	int		first;

	first = 0;
	fd = open(".heredoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		return (ft_fprintf(2, "minishell: heredoc.txt"), perror(":"), 0);
	y = 0;
	line = NULL;
	while (++sum)
	{
		ft_fprintf(0, ">");
		line = get_next_line(STDIN_FILENO);
		if (last_eof(line, eofs, &y, sum))
			break ;
		if (y == ft_count_words((const char **)eofs) - 1)
			write_in_heredoc(&first, fd, line, eofs);
		if (line)
			free(line);
		line = NULL;
	}
	return (1);
}

int	handle_heredoc(char **tokens, char **pipes_redirs)
{
	bool	error;
	char	**eofs;
	int		sum;
	int		size_tokens;

	if (!tokens)
		return (0);
	size_tokens = ft_count_words((const char **)tokens);
	sum = 0;
	error = false;
	if (error_in_heredoc(tokens, pipes_redirs, &error))
		return (0);
	eofs = find_eofs(&sum, tokens, pipes_redirs);
	if (!eofs || !create_heredoc(eofs, 0))
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
