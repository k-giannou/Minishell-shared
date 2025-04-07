/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:14:22 by locagnio          #+#    #+#             */
/*   Updated: 2025/04/06 20:48:55 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_child(char **env, t_minishell *mini)
{
	int	sig;

	sig = 0;
	free_btree(*mini->p_btree);
	signal(SIGQUIT, sigquit_handler);
	close_and_redirect_pipes(&mini->p, mini->p.i);
	sig = redir_if_needed(env, mini);
	if (is_buildin(mini->cmd_s[mini->p.i][0], 0))
		exec_buildin(mini->cmd_s[mini->p.i], mini, 0);
	else
		execute(mini->cmd_s, mini->p.i, env, mini);
	free_pipes(mini->p.pipes, mini->p.nb_pipes);
	if (mini->p.pids)
		free(mini->p.pids);
	if (mini->cmd_s_redirs)
		free(mini->cmd_s_redirs);
	free_dbl_tab(env);
	free_splits_array(&mini->cmd_s);
	free_all(mini, "all");
	exit(sig);
}

void	exec_child_pipe(char **env, t_minishell *mini)
{
	mini->p.pids[mini->p.i] = fork();
	if (mini->p.pids[mini->p.i] == -1)
		return (perror(RED "Error -> pid failure\n" RESET));
	if (mini->p.pids[mini->p.i] == 0)
		exec_child(env, mini);
}

int	son_program(char **env, t_minishell *mini, int redir)
{
	int	sig;

	sig = redir_if_needed(env, mini);
	if (will_exit(mini->cmd_s[mini->p.i]) && (mini && mini->p.nb_pipes == 0))
	{
		multi_free("1, 2, 1", mini->p.pids, env, mini->cmd_s_redirs, NULL);
		free_btree(*mini->p_btree);
	}
	if (is_buildin(mini->cmd_s[mini->p.i][0], 0) && !redir
		&& mini->p.nb_pipes == 0)
		exec_buildin(mini->cmd_s[mini->p.i], mini, 0);
	else if (!(is_buildin(mini->cmd_s[mini->p.i][0], 0)
		&& mini->p.nb_pipes == 0) && !mini->cmd_s_redirs[mini->p.i])
		exec_child_pipe(env, mini);
	close_curr_pipe(&mini->p, mini->p.i, mini->cmd_s[mini->p.i]);
	if (mini->p.nb_pipes == 0)
		return (waitpid(mini->p.pids[0], &sig, 0), get_sig(sig));
	if (mini->p.i == mini->p.nb_pipes)
		return (waitpid(mini->p.pids[mini->p.i - 1], &sig, 0), get_sig(sig));
	mini->p.i++;
	sig = son_program(env, mini, mini->cmd_s_redirs[mini->p.i]);
	return (waitpid(mini->p.pids[mini->p.i - 1], NULL, 0), sig);
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
	int		signal;

	mini->p.nb_pipes = pipe_count(the_tree);
	mini->cmd_s_redirs = (int *)ft_calloc(sizeof(int), (mini->p.nb_pipes + 1));
	mini->cmd_s = get_cmd_s(the_tree, 0, mini->p.nb_pipes, mini->cmd_s_redirs);
	mini->p.i = 0;
	mini->p.pids = (pid_t *)ft_calloc(sizeof(pid_t), (mini->p.nb_pipes + 1));
	if (!mini->p.pids)
		return (free(mini->cmd_s_redirs), free_splits_array(&mini->cmd_s),
			ft_fprintf(2, RED"Error : fail initiate pid's\n"RESET), -1);
	if (mini->p.nb_pipes != 0)
		create_pipes(&mini->p);
	else
		mini->p.pipes = NULL;
	signal = son_program(env, mini, mini->cmd_s_redirs[mini->p.i]);
	if (!is_the_cmd_exist(mini->cmd_s[mini->p.nb_pipes][0]))
		signal = 127;
	free_pipes(mini->p.pipes, mini->p.nb_pipes);
	multi_free("1, 2, 1", mini->p.pids, env, mini->cmd_s_redirs, NULL);
	free_splits_array(&mini->cmd_s);
	wait(NULL);
	return (signal);
}
