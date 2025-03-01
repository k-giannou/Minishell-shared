/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_r.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiannou <kgiannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:50:09 by kgiannou          #+#    #+#             */
/*   Updated: 2025/03/01 09:49:33 by kgiannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valid_filename(char **tab, char **ntab)
{
	struct stat statbuf;
	int	y;
	
	y = 0;
	while (tab[y])
	{
		if (ntab[y])
		{
			if (tab[y][0] == '>' || tab[y][0] == '<')//check if exist filename after > or <
			{	
				if (!tab[y + 1])//if there is not another tab, no filename
					return (ft_fprintf(2, "bash: syntax error near unexpected token `newline'\n"), 0);		
			}
			if (tab[y][0] == '<')//filename needs to exist
			{
				y++;
				if (stat(tab[y], &statbuf) != 0)//check if filename exist
					return (ft_fprintf(2, "bash: %s: No such file or directory\n", tab[y]), 0);
				if (access(tab[y], R_OK) != 0)
					return (ft_fprintf(2, "bash: %s: Permission denied\n", tab[y]), 0);
			}
		}
		y++;
	}
	return (1);
}


int	syntax_error_redir(char **tab, char **ntab)
{
	int	y;
	int	x;
	int	sum;
	
	y = 0;
	while(tab[y + 1])
	{
		if (ntab[y + 1])
		{
			x = 0;
			if ((ft_strcmp(tab[y], ">") == 0 || ft_strcmp(tab[y], ">>") == 0 || ft_strcmp(tab[y], "<") == 0 
				|| ft_strcmp(tab[y], "<<") == 0 || ft_strcmp(tab[y], "<>") == 0)
				&& (ft_strcmp(tab[y + 1], ">") == 0 || ft_strcmp(tab[y + 1], ">>") == 0
				|| ft_strcmp(tab[y + 1], "<" ) == 0 
				|| ft_strcmp(tab[y + 1], "<<") == 0  || ft_strcmp(tab[y + 1], "<>") == 0))
					return (ft_fprintf(2, "bash: syntax error near unexpected token `%s'\n", tab[y]), 1);
		}
		y++;
	}
	y = 0;
	while(tab[y])
	{
		if (ntab[y])
		{
			x = 0;
			sum = 0;
			if (ft_strcmp(tab[y], "><") == 0 || ft_strcmp(tab[y], "<>") == 0)
				return (ft_fprintf(2, "bash: syntax error near unexpected token `%c'\n", tab[y][x]), 1);
			while (tab[y][x] == '>' || tab[y][x] == '<')
			{
				sum++;
				if (sum > 2)
					return (ft_fprintf(2, "bash: syntax error near unexpected token `%c'\n", tab[y][x]), 1);
				x++;
			}
		}
		y++;
	}
	return (0);
}
