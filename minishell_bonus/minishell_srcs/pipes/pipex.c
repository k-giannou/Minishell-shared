/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:14:22 by locagnio          #+#    #+#             */
/*   Updated: 2025/04/04 18:00:51 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_first_arg(char *av)
{
	char	*first_arg;
	int		i;

	if (!av)
		return (NULL);
	first_arg = malloc(sizeof(char) * (ft_strclen(av, ' ') + 1));
	if (!first_arg)
		return (printf("error : couldn't get first arg"), exit(1), NULL);
	i = 0;
	while (av[i] && av[i] != ' ')
	{
		first_arg[i] = av[i];
		i++;
	}
	first_arg[i] = 0;
	return (first_arg);
}

void	exec_child(char **env, t_minishell *mini, char **split, char **redirs)
{
	int	sig;

	sig = 0;
	signal(SIGQUIT, sigquit_handler);
	close_and_redirect_pipes(&mini->p, mini->p.i);
	if (mini->cmd_s_redirs[mini->p.i])
	{
		split = ft_splitdup(mini->cmd_s[mini->p.i]);
		redirs = get_redir_split(mini, mini->p.i);
		sig = redir(mini, env, split, redirs);
		free_pipes_redirs(redirs, ft_count_words((const char **)split));
		free_dbl_tab(split);
	}
	else
		execute(mini->cmd_s, mini->p.i, env, mini);
	if (mini->p.i > 0)
		close(mini->p.pipes[mini->p.i - 1][0]);
	if (mini->p.pipes)
		free_pipes(mini->p.pipes, mini->p.nb_pipes);
	multi_free("1, 2, 1", mini->p.pids, env, mini->cmd_s_redirs, NULL);
	free_array_of_splits(mini->cmd_s);
	free_all(mini, "all");
	exit(sig);
}

int	son_program(char **env, t_minishell *mini)
{
	int	sig;

	sig = 0;
	if (will_exit(mini->cmd_s[mini->p.i]))
		multi_free("1, 2, 1", mini->p.pids, env, mini->cmd_s_redirs, NULL);
	if (is_buildin(mini->cmd_s[mini->p.i][0], 0))
		exec_buildin(mini->cmd_s[mini->p.i], mini, 0, mini->cmd_s);
	else
	{
		mini->p.pids[mini->p.i] = fork();
		if (mini->p.pids[mini->p.i] == -1)
			return (perror(RED "Error -> pid failure\n" RESET), -1);
		if (mini->p.pids[mini->p.i] == 0)
			exec_child(env, mini, NULL, NULL);
		else
			close_curr_pipe(&mini->p, mini->p.i, mini->cmd_s[mini->p.i]);
	}
	if (mini->p.nb_pipes == 0)
		return (waitpid(mini->p.pids[0], &sig, 0), get_sig(sig));
	if (mini->p.i == mini->p.nb_pipes)
		return (waitpid(mini->p.pids[mini->p.i - 1], &sig, 0), get_sig(sig));
	mini->p.i++;
	sig = son_program(env, mini);
	waitpid(mini->p.pids[mini->p.i - 1], NULL, 0);
	return (sig);
}

char	***get_cmd_s(t_btree *the_tree, int i, int nb_pipes, int *cmd_s_redirs)
{
	int		j;
	int		k;
	char	***cmd_s;

	cmd_s = (char ***)ft_calloc(sizeof(char **), (nb_pipes + 2));
	if (!cmd_s || !the_tree->tokens)
		return (printf("fail getting cmd's\n"), NULL);
	j = 0;
	k = 0;
	while (i < the_tree->len_arg && the_tree->tokens[i])
	{
		if (!ft_strncmp(the_tree->pipes_redirs[i], "|", 1))
			twenty_five_lines_bs(&j, &i, &k);
		else
		{
			while (the_tree->tokens[i]
				&& ft_strncmp(the_tree->pipes_redirs[i], "|", 1))
				if (isredir_str(the_tree->pipes_redirs[i++]))
					cmd_s_redirs[j] = 1;
			cmd_s[j] = ft_splitndup(the_tree->tokens, the_tree->len_arg, k, i);
		}
	}
	return (cmd_s[j + 1] = NULL, cmd_s);
}

int	pipex(t_minishell *mini, t_btree *the_tree, char **env)
{
	int		i;
	int		signal;

	i = -1;
	mini->p.nb_pipes = pipe_count(the_tree);
	mini->cmd_s_redirs = (int *)ft_calloc(sizeof(int), (mini->p.nb_pipes + 1));
	mini->cmd_s = get_cmd_s(the_tree, 0, mini->p.nb_pipes, mini->cmd_s_redirs);
	mini->p.i = 0;
	mini->p.pids = (pid_t *)ft_calloc(sizeof(pid_t), (mini->p.nb_pipes + 1));
	if (!mini->p.pids)
		return (free(mini->cmd_s_redirs), free_array_of_splits(mini->cmd_s),
			ft_fprintf(2, RED"Error : fail initiate pid's\n"RESET), -1);
	if (mini->p.nb_pipes != 0)
		create_pipes(&mini->p);
	else
		mini->p.pipes = NULL;
	signal = son_program(env, mini);
	free_pipes(mini->p.pipes, mini->p.nb_pipes);
	multi_free("1, 2, 1", mini->p.pids, env, mini->cmd_s_redirs, NULL);
	free_array_of_splits(mini->cmd_s);
	wait(NULL);
	return (signal);
}
