/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:21:49 by kgiannou          #+#    #+#             */
/*   Updated: 2025/02/26 17:45:01 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_r(t_redirs *r, t_minishell *mini)
{
	r->saved_in = dup(STDIN_FILENO);
	r->saved_in = dup(STDOUT_FILENO);
	if (r->saved_in == -1 || r->saved_out == -1)
		return (perror("dup failed"), 0);
	r->tab = copy_tokens(mini->tokens);
	r->y = 0;
	r->fd = -1;
	return (1);
}

int	redir_out(t_redirs *r)
{
	r->fd = -1;
	if (!ft_strcmp(r->tab[r->y], ">"))
		r->fd = open(r->tab[r->y + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (!ft_strcmp(r->tab[r->y], ">>"))
		r->fd = open(r->tab[r->y + 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (r->fd < 0)
	{
		ft_fprintf(2, "Bash: %s", r->tab[r->y + 1]);
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

int	redir_in(t_redirs *r)
{
	
	r->fd = -1;
	if (!ft_strcmp(r->tab[r->y], "<") || !ft_strcmp(r->tab[r->y], "<<"))
	{
		r->fd = open(r->tab[r->y + 1], O_RDONLY);
		if (r->fd < 0)
		{
			ft_fprintf(2, "Bash: %s", r->tab[r->y + 1]);
			perror(":");
			return (0);
		}
	}
	if (dup2(r->fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close (r->fd);
		return (0);
	}
	close(r->fd);
	return (1);
}

int	handle_files(t_minishell *mini, t_redirs *r)
{
	while (mini->tokens[r->y])//while tokens exist
	{
		find_tab(&(r->y), mini->pipes_redirs, mini->tokens);
		if (!mini->tokens[r->y])
			break ;
		if (!ft_strcmp(r->tab[r->y], ">") || !ft_strcmp(r->tab[r->y], ">>"))//redir stdout
		{
			if (!redir_out(r))
				return (0);
			r->type = REDIR_OUT;
		}
		else if (!ft_strcmp(r->tab[r->y], "<") || !ft_strcmp(r->tab[r->y], "<<"))//redir stdin
		{
			if (!redir_in(r))
				return (0);
			r->type = REDIR_IN;
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

int	redir(t_minishell *mini, char **env)
{
	char *path;
	char	**split_command;
	t_redirs	r;
	
	if (!mini)
		return (-1);
	if (syntax_error_redir(mini->tokens, mini->pipes_redirs) || !valid_filename(mini->tokens, mini->pipes_redirs))//verify if the synthaxe is good
		return (-1);
	r = mini->r;
	if (!init_r(&r, mini))//init r
		return (-1);
	split_command = NULL;
	path = NULL;
	if (is_buildin(mini->tokens[0], 0))//if it's buildin
	{
		if (!handle_files(mini, &r))//check for redirections
			return (restore_dup(&r), -1);//reset the input and output if there's none
		split_command = join_command_free_tab(r.tab, mini);//join the arguments and the command together
		exec_buildin(split_command, mini, 0);//go build this shit
	}
	else
 	{
		pid_t pid = fork();//create a process
		if (pid == -1)
			return (perror("fork"), -1);
		if (pid == 0)
		{
			if (!handle_files(mini, &r))//check for redirections
				return (restore_dup(&r), -1);//reset the input and output if there's none
			split_command = join_command_free_tab(r.tab, mini);//join the arguments and the command together
			path = find_path(split_command[0], env);//search for the path of the command
			if (!path)
			{
				perror(RED "Error -> issue finding path\n" RESET);
				free_dbl_tab(split_command);
				return (restore_dup(&r), -1);//reset the input and output
			}
			if (execve(path, split_command, env) == -1)//execute this shit
			{
				free(path);
				free_dbl_tab(split_command);
				perror(RED "Error -> execution failure\n" RESET);
				return (restore_dup(&r), -1);//reset the input and output
			}
		}
		else
			waitpid(pid, NULL, 0);
	}
	if (path)
		free(path);
	return (restore_dup(&r), free_dbl_tab(split_command), 0);//reset the input and output and free
}
