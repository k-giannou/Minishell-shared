/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:07:06 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/08 21:03:30 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	strcmp_64(char *nptr)
{
	size_t	len_max;
	size_t	len_min;
	int		i;

	i = -1;
	len_max = ft_strlen(INT64_Max);
	len_min = ft_strlen(INT64_Min);
	if ((nptr[0] != '-' && ft_strlen(nptr) > len_max)
		|| (nptr[0] == '-' && ft_strlen(nptr) > len_min))
		return (free(nptr), 1);
	else if (nptr[0] != '-' && ft_strlen(nptr) == len_max)
	{
		while (nptr[++i])
			if (nptr[i] > INT64_Max[i])
				return (free(nptr), 1);
	}
	else if (nptr[i++] == '-' && ft_strlen(nptr) == len_min)
	{
		while (nptr[++i])
			if (nptr[i] > INT64_Min[i])
				return (free(nptr), 1);
	}
	return (free(nptr), 0);
}

void	error_exit(const char *str, int nb)
{
	if (nb == 1)
		ft_fprintf(2, "exit\nminishell: exit: %s: numeric argument required\n", str);
	else
		ft_fprintf(2, "minishell: exit: too many arguments\n");
}

int	valid_nb(char *str)
{
	int	i;

	i = 0;
	while (ft_iswhitespace(str[i]))
		i++;
	if (str[i] && (ft_isnum(str[i]) || str[i] == '+' || str[i] == '-'))
		i++;
	else
		return (0);
	while (str[i])
		if (!ft_isnum(str[i++]))
			return (0);
	return (1);
}

void	ft_exit(t_minishell *mini)
{
	int		i;
	int64_t	nb;

	i = 1;
	nb = 0;
	if (mini->tokens && mini->tokens[0] && mini->tokens[0][0]
		&& mini->tokens[1])
	{
		if (!valid_nb(mini->tokens[1])
			|| strcmp_64(
				ft_remove_from_string(mini->tokens[1], " \n\v\f\r+", 0)))
			return (g_signal = 2, error_exit(mini->tokens[1], 1),
				free_all(mini, "all"), exit(2));
		nb = ft_atoi64(mini->tokens[1]);
	}
	if (mini->tokens && mini->tokens[0] && mini->tokens[0][0] && mini->tokens[1]
		&& mini->tokens[2])
		return (g_signal = 1, error_exit(mini->tokens[2], 2));
	return (g_signal = nb % 256, printf("exit\n"), free_all(mini, "all"),
			exit(nb % 256));
}
