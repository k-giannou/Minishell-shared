/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:19:00 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/10 16:49:03 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	valid_quotes(char c, bool *sgl_q, bool *dbl_q)
{
	if (!(*sgl_q) && !(*dbl_q))
	{
		if (c == SGL_Q)
			(*sgl_q) = 1;
		else if (c == DBL_Q)
			(*dbl_q) = 1;
	}
	else if ((*sgl_q) || (*dbl_q))
	{
		if (c == SGL_Q && (*sgl_q) && !(*dbl_q))
			(*sgl_q) = 0;
		else if (c == DBL_Q && (*dbl_q) && !(*sgl_q))
			(*dbl_q) = 0;
	}
}
