/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_splitjoin_n_free.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:07:25 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/25 19:20:51 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

static bool	correct_format(char *str_char)
{
	int	i;

	i = 0;
	while (str_char[i])
	{
		if (ft_isnum(str_char[i]) || str_char[i] == '-' || str_char[i] == '+')
			i++;
		else if (ft_strcmp (str_char + i, ", ") && i != 0)
			i += 2;
		else
			return (0);
	}
	return (1);
}

int	has_to_be_freed(t_msjnf v, int *tab_inc)
{
	while (v.tabs_to_free[*tab_inc] < v.cur_str && *tab_inc < v.tab_len - 1)
		(*tab_inc)++;
	if (*tab_inc == v.tab_len - 1 && v.tabs_to_free[*tab_inc] < v.cur_str)
		return (0);
	if (v.tabs_to_free[*tab_inc] == v.cur_str)
		return (1);
	return (0);
}

char	**multi_spitjoin_n_free2(t_msjnf v)
{
	if (v.tabs_to_free && has_to_be_freed(v, &v.tab_increment))
		free_dbl_tab(v.arg);
	if (!v.new_split)
		return (ft_putstr_fd("fail join\n", 2), NULL);
	v.arg = va_arg(v.args, char **);
	v.cur_str = 2;
	while (v.arg)
	{
		v.new_split = ft_splitjoin_n_free(v.new_split, v.arg, 1);
		if (v.tabs_to_free && has_to_be_freed(v, &v.tab_increment))
			free_dbl_tab(v.arg);
		if (!v.new_split)
			return (ft_putstr_fd("fail join and free\n", 2), NULL);
		v.arg = va_arg(v.args, char **);
		v.cur_str++;
	}
	va_end(v.args);
	free(v.tabs_to_free);
	return (v.new_split);
}

/* Join an infinite amount of splits and free the wished tabs.

	The last argument should be NULL to interrupt the
	function correctly, otherwise,
	undefined outcome may happened.

	If one split is passed in argument, it behaves like strdup(s1).
	
	The string "to_free" follows the rules of the function strchar_to_strint :
	- Each numbers represent the position of
	each split that should be freed, starting
	at position zero, if the number exceeds the
	limits of the numbers of splits, they
	will be ignored.
	- The string must follow the format : "n1, n2, ..., nn".
	- If the format isn't respected, or if the string is NULL or empty, the
	string will be considered NULL and no split will be freed
	*/
char	**multi_splitjoin_n_free(char *to_free, char **s1, ...)
{
	t_msjnf	v;

	if (!s1)
		return (NULL);
	v = (t_msjnf){0};
	if (to_free && correct_format(to_free))
	{
		v.tabs_to_free = strchar_to_strint(to_free);
		v.tab_len = ft_strintlen(to_free);
	}
	va_start(v.args, s1);
	v.arg = va_arg(v.args, char **);
	if (!v.arg)
	{
		v.new_split = ft_splitdup(s1);
		if (v.tabs_to_free && has_to_be_freed(v, &v.tab_increment))
			free_dbl_tab(s1);
		return (va_end(v.args), free(v.tabs_to_free), v.new_split);
	}
	v.new_split = ft_splitjoin((const char **)s1, (const char **)v.arg);
	if (v.tabs_to_free && has_to_be_freed(v, &v.tab_increment))
		free_dbl_tab(s1);
	v.cur_str++;
	return (multi_spitjoin_n_free2(v));
}
