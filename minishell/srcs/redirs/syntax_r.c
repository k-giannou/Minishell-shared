/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_r.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiannou <kgiannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:50:09 by kgiannou          #+#    #+#             */
/*   Updated: 2025/03/05 15:26:39 by kgiannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valid_filename(char **tab, char **ntab)
{
	struct stat	statbuf;
	int			y;

	y = 0;
	while (tab[y])
	{
		if (ntab[y])
		{
			if (tab[y][0] == '>' || tab[y][0] == '<')
			{
				if (!tab[y + 1])
					return (ft_fprintf(2, "bash: syntax error near \
					unexpected token `newline'\n"), 0);
			}
			if (tab[y][0] == '<')
			{
				y++;
				if (stat(tab[y], &statbuf) != 0)
					return (ft_fprintf(2,
							"bash: %s: No such file \
							or directory\n", tab[y]), 0);
				if (access(tab[y], R_OK) != 0)
					return (ft_fprintf(2,
							"bash: %s: Permission denied\n", tab[y]), 0);
			}
		}
		y++;
	}
	return (1);
}

int	syntax_error_redir(char **tab, char **ntab)
{
	int	y;

	y = 0;
	while (tab[y + 1])
	{
		if (ntab[y + 1])
		{
			if (ntab[y] && ntab[y + 1])
				return (ft_fprintf(2,
						"bash: syntax error near unexpected \
						token `%s'\n", tab[y + 1]), 1);
		}
		y++;
	}
	y = 0;
	while (tab[y])
	{
		if (ntab[y])
		{
			if (!ft_strcmp(tab[y], "><") || !ft_strcmp(tab[y], "<>")
				|| ft_strsrch(tab[y], "<<<") || ft_strsrch(tab[y], ">>>"))
				return (ft_fprintf(2,
						"bash: syntax error near unexpected token `%c'\n",
						tab[y][1]), 1);
		}
		y++;
	}
	return (0);
}
