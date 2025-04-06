/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:07:06 by locagnio          #+#    #+#             */
/*   Updated: 2025/04/06 16:23:09 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	strcmp_64_mini(char *nptr)
{
	size_t	len_max;
	size_t	len_min;
	int		i;

	i = -1;
	len_max = ft_strlen(INT64_MAX_ATOI);
	len_min = ft_strlen(INT64_MIN_ATOI);
	if ((nptr[0] != '-' && ft_strlen(nptr) > len_max)
		|| (nptr[0] == '-' && ft_strlen(nptr) > len_min))
		return (1);
	else if (nptr[0] != '-' && ft_strlen(nptr) == len_max)
	{
		while (nptr[++i])
			if (nptr[i] > INT64_MAX_ATOI[i])
				return (1);
	}
	else if (nptr[++i] == '-' && ft_strlen(nptr) == len_min)
	{
		while (nptr[++i])
			if (nptr[i] > INT64_MIN_ATOI[i])
				return (1);
	}
	free(nptr);
	return (0);
}

void	error_exit(const char *str, int nb)
{
	if (nb == 1)
		ft_fprintf(2,
			"exit\nminishell: exit: %s: numeric argument required\n", str);
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

void	ft_exit(char **tokens, t_minishell *mini)
{
	int64_t	nb;
	char *tmp;

	nb = 0;
	tmp = NULL;
	if (tokens && tokens[0] && tokens[0][0]
		&& tokens[1])
	{
		tmp = ft_remove_from_string(tokens[1], " \n\v\f\r+", 0);
		if (!valid_nb(tokens[1]) || strcmp_64_mini(tmp))
			return (g_signal = 2, error_exit(tokens[1], 1),
				free_splits_array(&mini->cmd_s), free_all(mini, "all"), exit(2));
		nb = ft_atoi64(tokens[1]);
	}
	if (tokens && tokens[0] && tokens[0][0] && tokens[1]
		&& tokens[2])
		return (g_signal = 1, error_exit(tokens[2], 2));
	return (g_signal = nb % 256, printf("exit\n"), 
		free_splits_array(&mini->cmd_s), free_all(mini, "all"), exit(nb % 256));
}
