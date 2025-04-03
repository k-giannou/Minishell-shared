/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:01:31 by locagnio          #+#    #+#             */
/*   Updated: 2025/04/03 20:01:33 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler(int sig)
{
	g_signal = sig + 128;
	write(1, "\b\n", 2);
	ft_fprintf(2, "sigint_handler\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_handler2(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	ft_fprintf(2, "sigint_handler2\n");
}

void	sigquit_handler(int sig)
{
	(void)sig;
	ft_fprintf(2, "Quit (code dumped)\n");
}

void	sig_init(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
