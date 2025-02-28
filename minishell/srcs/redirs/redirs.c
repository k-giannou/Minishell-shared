/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:21:49 by kgiannou          #+#    #+#             */
/*   Updated: 2025/02/28 19:36:25 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_r(t_redirs *r, char **tokens)
{
	r->saved_in = dup(STDIN_FILENO);
	r->saved_in = dup(STDOUT_FILENO);
	if (r->saved_in == -1 || r->saved_out == -1)
		return (perror("dup failed"), 0);
	r->tab = ft_splitdup(tokens);
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

int	handle_heredoc(t_redirs *r)
{
	char	*line;
	
		r->fd = open(".heredoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (r->fd < 0)
		{
			ft_fprintf(2, "Bash: heredoc.txt");
			perror(":");
			return (0);
		}
		ft_fprintf(0, ">");
		line = get_next_line(STDIN_FILENO);
		while (line)
		{
			if (ft_strncmp(line, r->tab[r->y + 1], ft_strlen(r->tab[r->y + 1])) == 0
				&& line[ft_strlen(r->tab[r->y + 1])] == '\n')
			{
				free (line);
				break ;
			}
			ft_fprintf(0, ">");
			write(r->fd, line, ft_strlen(line));
			free(line);
			line = NULL;
			line = get_next_line(STDIN_FILENO);
		}
		r->type = HEREDOC;
		return (1);
}

int	redir_in(t_redirs *r, int make_dup)
{
	
	r->fd = -1;
	if (!ft_strcmp(r->tab[r->y], "<"))
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
	else if (!ft_strcmp(r->tab[r->y], "<<"))
	{
		if (!handle_heredoc(r))
		{
			ft_fprintf(2, "Heredoc failed.");
			return (0);
		}
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
		if (r->type == HEREDOC)
		{
			free (r->tab[r->y]);
			r->tab[r->y++] = NULL;
			free (r->tab[r->y]);
			r->tab[r->y++] = ft_strdup(".heredoc.txt");
			
		}
		else
		{
			free (r->tab[r->y]);
			r->tab[r->y++] = NULL;
			free (r->tab[r->y]);
			r->tab[r->y++] = NULL;
		}
	}
	return (1);
}

int	redir(t_minishell *mini, char **env, char **tokens, char **pipes_redirs)
{
	char *path;
	int	i;
	pid_t pid;
	int	fd[2];

	if (!mini || !env || !tokens || !pipes_redirs)
		return (-1);
	if (syntax_error_redir(tokens, pipes_redirs) || !valid_filename(tokens, pipes_redirs))//verify if the synthaxe is good
		return (-1);
	if (!init_r(&mini->r, tokens))//init r
		return (-1);
	path = NULL;
	i = 0;
	if (pipe(fd) == -1)
		return (perror(RED "Error -> issue creating pipe\n" RESET), exit(1), 1);//je creer mon pipe
	pid = fork();//create a process
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		close(fd[0]);//je ferme la lecture
		dup2(fd[1], STDOUT_FILENO);//je redirige la sortie standard dans l'ecriture du pipe
		if (!is_buildin(tokens[0], 0))//if it's buildin
			i = 1;
		if (!handle_files(tokens, pipes_redirs, &mini->r, i))//check for redirections
			restore_dup(&mini->r);//reset the input and output if there's none
		join_command_free_tab(mini->r.tab, tokens);//join the arguments and the command together
		if (is_buildin(tokens[0], 0))//if it's buildin
			exec_buildin(mini->r.tab, mini, 0);//go build this shit
		else
		{	
			path = find_path(mini->r.tab[0], env);//search for the path of the command
			if (!path)
			{
				perror(RED "Error -> issue finding path\n" RESET);
				free_dbl_tab(mini->r.tab);
				restore_dup(&mini->r);//reset the input and output
			}
			if (execve(path, mini->r.tab, env) == -1)//execute this shit
			{
				free(path);
				free_dbl_tab(mini->r.tab);
				perror(RED "Error -> execution failure\n" RESET);
				restore_dup(&mini->r);//reset the input and output
			}
			close(fd[1]);
			free_all(mini, "all");
			free_dbl_tab(env);
			free_pipes_redirs(pipes_redirs, ft_count_words(tokens));
			free_dbl_tab(tokens);
			exit(0);
		}
	}
	else
	{
		close(fd[1]);//je ferme l'ecriture du pipe
		waitpid(pid, NULL, 0);//j'attends le processus enfant
	}
	if (path)
		free(path);
	if (pipes_redirs)
		free_pipes_redirs(pipes_redirs, ft_count_words(tokens));
	if (tokens)
		free_dbl_tab(tokens);
	return (restore_dup(&mini->r), free_dbl_tab(mini->r.tab), 0);//reset the input and output and free
}
