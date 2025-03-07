/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 20:17:08 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/07 20:25:16 by locagnio         ###   ########.fr       */
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

void	ft_print_dlb_tabs(char **tab, char *arg)
{
	int	i;

	i = 0;
	printf("%s : ", arg);
	while (tab && tab[i])
		printf("|%s| ", tab[i++]);
	printf("\n");
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

void	ft_print_export(t_env *v, bool sign, bool inside)
{
	int		i;

	while (v != NULL)
	{
		printf("declare -x ");
		i = 0;
		while (v->data[i])
		{
			if (v->data[i] == '=' && !inside)
			{
				sign = true;
				inside = true;
				printf("%c", v->data[i++]);
				printf("\"");
			}
			printf("%c", v->data[i++]);
		}
		if (v->data[i] == '\0' && sign)
			printf("\"");
		printf("\n");
		v = v->next;
		sign = false;
		inside = false;
	}
}

void	print_list(t_env *L)
{
	if (!L)
		printf("(null)");
	while (L)
	{
		printf("%s\n", L->data);
		L = L->next;
	}
}
