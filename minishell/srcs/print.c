/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 20:17:08 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/26 20:53:43 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	welcome(void)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 50000000;
	str = CYAN ITALIC" Welcome..."RESET CYAN"\n to...\n"BOLD GREEN
		" MINISHELL !\n\n"RESET;
	while (str[i])
	{
		write(1, &str[i++], 1);
		while (j > 0)
			j--;
		j = 50000000;
	}
}

void	error(void)
{
	perror(RED "Error ");
	exit(EXIT_FAILURE);
}

void	ft_print_dlb_tabs(char **tab, char *arg)
{
	int	i;

	i = 0;
	printf("%s : ", arg);
	while (tab && tab[i])
		printf("|%s| ", tab[i++]);
	printf("\n");
}

void	ft_putcstr_fd(char *s, int fd, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	print_pipes_redirs(char **split, int nb_words)
{
	int	j;

	j = 0;
	printf("tab with pipes and redirs : ");
	while (j < nb_words)
	{
		if (split[j])
			printf("|%s| ", split[j]);
		else
			printf("(null) ");
		j++;
	}
	printf("\n");
}
