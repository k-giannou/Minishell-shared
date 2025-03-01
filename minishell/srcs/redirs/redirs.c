/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiannou <kgiannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:21:49 by kgiannou          #+#    #+#             */
/*   Updated: 2025/03/01 16:01:02 by kgiannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_r(t_redirs *r, char **tokens)
{
	r->saved_in = dup(STDIN_FILENO);
	r->saved_in = dup(STDOUT_FILENO);
	if (r->saved_in == -1 || r->saved_out == -1)
		return (perror("dup failed"), 0);
	r->tab = copy_tokens(tokens);
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

int	redir_in(t_redirs *r, int make_dup)
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
	while (tokens[r->y])//while tokens exist
	{
		find_tab(&(r->y), pipes_redirs, tokens);
		if (!tokens[r->y])
			break ;
		if (!ft_strcmp(r->tab[r->y], ">") || !ft_strcmp(r->tab[r->y], ">>"))//redir stdout
		{
			if (!redir_out(r))
				return (0);
			r->type = REDIR_OUT;
		}
		else if (!ft_strcmp(r->tab[r->y], "<") || !ft_strcmp(r->tab[r->y], "<<"))//redir stdin
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

int	redir(t_minishell *mini, char **env, char **tokens, char **pipes_redirs)
{
	char *path;
	
	if (!mini || !env || !tokens || !pipes_redirs)
		return (free_dbl_tab(env), -1);
	if (heredoc(tokens, pipes_redirs))
	{
		if (!handle_heredoc(tokens, pipes_redirs)) 
			return (free_dbl_tab(env), -1);
	}
	//printf(" <<< valid >>>\n");
	//return (1);
	if (syntax_error_redir(tokens, pipes_redirs) || !valid_filename(tokens, pipes_redirs))//verify if the synthaxe is good
		return (free_dbl_tab(env), -1);
	if (!init_r(&mini->r, tokens))//init r
		return (free_dbl_tab(env), -1);
	path = NULL;
	if (is_buildin(tokens[0], 0))//if it's buildin
	{
		if (!handle_files(tokens, pipes_redirs, &mini->r, 0))//check for redirections
			return (free_dbl_tab(env), restore_dup(&mini->r), -1);//reset the input and output if there's none
		join_command_free_tab(mini->r.tab, tokens);//join the arguments and the command together
		exec_buildin(mini->r.tab, mini, 0);//go build this shit
	}
	else
 	{
		pid_t pid = fork();//create a process
		if (pid == -1)
			return (free_dbl_tab(env), perror("fork"), -1);
		if (pid == 0)
		{
			if (!handle_files(tokens, pipes_redirs, &mini->r, 1))//check for redirections
				return (restore_dup(&mini->r), -1);//reset the input and output if there's none
			join_command_free_tab(mini->r.tab, tokens);//join the arguments and the command together
			path = find_path(mini->r.tab[0], env);//search for the path of the command
			if (!path)
			{
				perror(RED "Error -> issue finding path\n" RESET);
				free_dbl_tab(mini->r.tab);
				return (restore_dup(&mini->r), -1);//reset the input and output
			}
			if (execve(path, mini->r.tab, env) == -1)//execute this shit
			{
				free(path);
				free_dbl_tab(mini->r.tab);
				perror(RED "Error -> execution failure\n" RESET);
				return (restore_dup(&mini->r), -1);//reset the input and output
			}
		}
		else
			waitpid(pid, NULL, 0);
	}
	if (path)
		free(path);
	free_dbl_tab(env);
	return (restore_dup(&mini->r), free_dbl_tab(mini->r.tab), 0);//reset the input and output and free
}
