/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:21:49 by kgiannou          #+#    #+#             */
/*   Updated: 2025/04/04 17:50:31 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redir_out(t_redirs *r)
{
	r->fd = -1;
	if (!ft_strcmp(r->tab[r->y], ">"))
		r->fd = open(r->tab[r->y + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (!ft_strcmp(r->tab[r->y], ">>"))
		r->fd = open(r->tab[r->y + 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (r->fd < 0)
	{
		ft_fprintf(2, "minishell: %s", r->tab[r->y + 1]);
		perror(":");
		return (0);
	}
	if (dup2(r->fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close (r->fd);
		return (0);
	}
	close(r->fd);
	return (1);
}

int	redir_in(t_redirs *r, int make_dup)
{
	r->fd = -1;
	if (!ft_strcmp(r->tab[r->y], "<") || !ft_strcmp(r->tab[r->y], "<<"))
	{
		r->fd = open(r->tab[r->y + 1], O_RDONLY);
		if (r->fd < 0)
		{
			ft_fprintf(2, "minishell: %s", r->tab[r->y + 1]);
			perror(":");
			return (0);
		}
		r->type = REDIR_IN;
	}
	if (make_dup == 1)
	{
		if (dup2(r->fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close (r->fd);
			return (0);
		}
	}
	close(r->fd);
	return (1);
}

int	handle_files(char **tokens, char **pipes_redirs, t_redirs *r, int make_dup)
{
	while (tokens[r->y])
	{
		find_tab(&(r->y), pipes_redirs, tokens);
		if (!tokens[r->y])
			break ;
		if (!ft_strcmp(r->tab[r->y], ">") || !ft_strcmp(r->tab[r->y], ">>"))
		{
			if (!redir_out(r))
				return (0);
			r->type = REDIR_OUT;
		}
		else if (!ft_strcmp(r->tab[r->y], "<")
			|| !ft_strcmp(r->tab[r->y], "<<"))
		{
			if (!redir_in(r, make_dup))
				return (0);
		}
		else
			return (0);
		free (r->tab[r->y]);
		r->tab[r->y++] = NULL;
		free (r->tab[r->y]);
		r->tab[r->y++] = NULL;
	}
	return (1);
}

int	handle_no_buildin_redir(char **env, char **tokens,
	char **pipes_redirs, t_minishell *mini)
{
	char	*path;
	pid_t	pid;

	path = NULL;
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 0);
	if (pid == 0)
	{
		if (!handle_files(tokens, pipes_redirs, &mini->r, 1))
		{
			restore_dup(&mini->r);
			exit (1);
		}
		join_command_free_tab(mini->r.tab, tokens);
		path_and_execute(path, mini, env);
	}
	else
		waitpid(pid, NULL, 0);
	if (path)
		free(path);
	return (1);
}

int	redir(t_minishell *mini, char **env, char **tokens, char **pipes_redirs)
{
	if (!mini || !env || !tokens || !pipes_redirs)
		return (1);
	if (heredoc(tokens, pipes_redirs))
	{
		if (!handle_heredoc(tokens, pipes_redirs))
			return (1);
	}
	if (syntax_error_redir(tokens, pipes_redirs))
		return (2);
	if (!valid_filename(tokens, pipes_redirs)
		|| !init_r(&mini->r, tokens))
		return (1);
	if (is_buildin(tokens[0], 0))
	{
		if (!handle_files(tokens, pipes_redirs, &mini->r, 0))
			return (restore_dup(&mini->r), 1);
		join_command_free_tab(mini->r.tab, tokens);
		exec_buildin(mini->r.tab, mini, 0, NULL);
	}
	else if (!handle_no_buildin_redir(env, tokens, pipes_redirs, mini))
		return (1);
	unlink(".heredoc.txt");
	return (restore_dup(&mini->r),
		free_dbl_tab(mini->r.tab), 0);
}
