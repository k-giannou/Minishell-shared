/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_r.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:50:09 by kgiannou          #+#    #+#             */
/*   Updated: 2025/04/06 16:50:51 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_mess_two(char *str)
{
	ft_fprintf(2, "minishell: %s: Permission denied\n", str);
}

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
					return (print_mess(NULL, 0, NULL, "\n"), 0);
			}
			if (tab[y][0] == '<')
			{
				y++;
				if (stat(tab[y], &statbuf) != 0)
					return (print_mess(NULL, 0, tab[y], NULL), 0);
				if (access(tab[y], R_OK) != 0)
					return (print_mess_two(tab[y]), 0);
			}
		}
		y++;
	}
	return (1);
}

void	print_mess(char *str1, char c, char *str2, char *str3)
{
	if (str1)
	{
		ft_fprintf(2, "minishell: syntax error near unexpected token ");
		ft_fprintf(2, "`%s'\n", str1);
	}
	else if (str2)
		ft_fprintf(2, "minishell: %s: No such file or directory\n", str2);
	else if (str3)
	{
		ft_fprintf(2, "minishell: syntax error near unexpected token ");
		ft_fprintf(2, "`newline'\n");
	}
	else
	{
		ft_fprintf(2, "minishell: syntax error near unexpected token");
		ft_fprintf(2, " `%c'\n", c);
	}
}

int	syntax_error_redir(char **tab, char **ntab)
{
	int	y;

	y = 0;
	while (tab[y + 1])
	{
		if (ntab[y + 1])
		{
			if (isredir_pipex(ntab[y]) && isredir_pipex(ntab[y + 1]))
				return (print_mess(tab[y + 1], 0, NULL, NULL), 1);
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
				return (print_mess(NULL, tab[y][1], NULL, NULL), 1);
		}
		y++;
	}
	return (0);
}
