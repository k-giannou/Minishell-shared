/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_r2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiannou <kgiannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:20:47 by kgiannou          #+#    #+#             */
/*   Updated: 2025/03/20 16:00:01 by kgiannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	write_in_heredoc(int *first, int fd, char *line, char **eofs)
{
	(*first)++;
	if (*first != 1 || ft_count_words(eofs) == 1)
		write(fd, line, ft_strlen(line));
}

int	init_r(t_redirs *r, char **tokens)
{
	r->saved_in = dup(STDIN_FILENO);
	r->saved_out = dup(STDOUT_FILENO);
	if (r->saved_in == -1 || r->saved_out == -1)
		return (perror("dup failed"), 0);
	r->tab = copy_tokens(tokens);
	r->y = 0;
	r->fd = -1;
	return (1);
}

void	restore_and_free(char **tab1, char *path, t_redirs *r)
{
	perror(RED "Error -> issue finding path or execve\n" RESET);
	free_dbl_tab(tab1);
	restore_dup(r);
	if (path)
		free(path);
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

void	restore_dup(t_redirs *r)
{
	if (r->saved_out != -1)
	{
		dup2(r->saved_out, STDOUT_FILENO);
		close(r->saved_out);
	}
	if (r->saved_in != -1)
	{
		dup2(r->saved_in, STDIN_FILENO);
		close(r->saved_in);
	}
}
