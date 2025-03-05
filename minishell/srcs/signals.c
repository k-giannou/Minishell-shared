/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:01:31 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/04 17:16:25 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler(int sig)
{
	g_signal = sig;
	write(1, "\b\b\n", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	sig_init(void)
{
	signal(SIGINT, sigint_handler);
}
