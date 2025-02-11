/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:01:31 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/11 18:22:58 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sigint_handler(int sig)
{
	g_signal = sig;
	write(1, "\b\n", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void sigquit_handler(int sig)
{
	g_signal = sig;
	printf("^\\Quit (core dumped)\n");
}

void	sig_init(void)
{
	signal(SIGINT, sigint_handler);  // Gérer SIGINT (Ctrl+C)
	/* signal(SIGQUIT, sigquit_handler); */
}
