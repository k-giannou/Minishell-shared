/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:46:16 by locagnio          #+#    #+#             */
/*   Updated: 2025/04/06 16:22:41 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tokens_splits(char ***tokens, char ***p_r, int len_tokens)
{
	
	if (*p_r)
		free_pipes_redirs(*p_r, len_tokens);
	free_dbl_tab(*tokens);
	*tokens = NULL;
	*p_r = NULL;
}

void	free_splits_array(char ****cmd_s)
{
	int	j;

	if (!(*cmd_s) || !(*cmd_s)[0])
		return ;
	j = 0;
	while ((*cmd_s)[j])
		free_dbl_tab((*cmd_s)[j++]);
	if ((*cmd_s))
		free((*cmd_s));
	(*cmd_s) = NULL;
}
