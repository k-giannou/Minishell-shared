/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:07:06 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/25 21:04:52 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* void	ft_exit(t_minishell *mini, char **line)
{
	char	*str;

	str = ft_readline("Are you sure ? [yes/no]\n", mini);
	if (!ft_strcmp("yes", str))
		return (free(str), free_all(mini, "all"), exit(0));
	else if (!ft_strcmp("no", str))
		ft_fprintf(1, "\nYeh, "UNDERLINE BOLD"you better NOT !"RESET" 😈\n");
	else
		ft_fprintf(1, "\nYou retard sh*t ! 💩\n", mini);
	free(str);
} */

int	strcmp_64(const char *nptr)
{
	size_t len_max;
	size_t len_min;

	len_max = ft_strlen(INT64_Max);
	len_min = ft_strlen(INT64_Min);
	if (nptr[0] != '-' && ft_strlen(nptr) > len_max)
		return (1);
	else if (nptr[0] == '-' && ft_strlen(nptr) > len_min)
		return (1);
	else if (nptr[0] != '-' && ft_strlen(nptr) == len_min
		&& !ft_strncmp(nptr, INT64_Max, len_max - 1)
		&& nptr[len_max] > INT64_Max[len_max])
		return (1);
	else if (nptr[0] == '-' && ft_strlen(nptr) == len_min
		&& !ft_strncmp(nptr, INT64_Max, len_min - 1)
		&& nptr[len_min] > INT64_Max[len_min])
		return (1);
	return (0);
}

void	error_exit(const char *str, int nb)
{
	if (nb == 1)
		ft_fprintf(2, "exit\nbash: exit: %s: numeric argument required\n", str);
	else
		ft_fprintf(2, "bash: exit: too many arguments\n");
}

int valid_nb(char *str)
{
	int i;

	i = 0;
	while (ft_iswhitespace(str[i]))
		i++;
	if (ft_isdigit(str[i]) || str[i] == '+' || str[i] == '-')
		i++;
	else
		return (0);
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}

void	ft_exit(t_minishell *mini)
{
	int i;
	int64_t nb;

	i = 1;
	nb = 0;
	if (mini->tokens[1])
	{
		if (!valid_nb(mini->tokens[1]) || strcmp_64(mini->tokens[1]))
			return (error_exit(mini->tokens[1], 1), free_all(mini, "all"),
				exit(2));
		nb = ft_atoi64(mini->tokens[1]);
	}
	if (mini->tokens[1] && mini->tokens[2])
		return (error_exit(mini->tokens[2], 2));
	return (printf("exit\n"), free_all(mini, "all"), exit(nb % 256));
}
