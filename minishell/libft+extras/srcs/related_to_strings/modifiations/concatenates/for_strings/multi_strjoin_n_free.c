/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_strjoin_n_free.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiannou <kgiannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:07:25 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/21 12:43:14 by kgiannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

typedef struct s_mjnf
{
	char	*arg;
	va_list	args;
	char	*new_string;
	int		*tabs_to_free;
	int		cur_str;
	int		tab_increment;
	int		tab_len;
}	t_mjnf;

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

int	has_to_be_freed(t_mjnf v, int *tab_inc)
{
	while (v.tabs_to_free[*tab_inc] < v.cur_str
		&& *tab_inc < v.tab_len - 1)//si la position dans le tableau est inferieur a la position du tableau actuel
		(*tab_inc)++;//je vais chercher une valeur egale ou superieure
	if (*tab_inc == v.tab_len - 1 && v.tabs_to_free[*tab_inc] < v.cur_str)//si je suis arriver a la fin du tableau et que ca ne correspond pas a la derniere valeur
		return (0);
	if (v.tabs_to_free[*tab_inc] == v.cur_str)//si la position correspond, je free.
		return (1);
	return (0);
}

char	*multi_join_n_free2 (t_mjnf v)
{
	if (v.tabs_to_free && has_to_be_freed(v, &v.tab_increment))
		free(v.arg);
	if (!v.new_string)
		return (ft_putstr_fd("fail join\n", 2), NULL);
	v.arg = va_arg(v.args, char *);
	v.cur_str = 2;
	while (v.arg)
	{
		v.new_string = ft_strjoin_n_free(v.new_string, v.arg, 1);
		if (v.tabs_to_free && has_to_be_freed(v, &v.tab_increment))
			free(v.arg);
		if (!v.new_string)
			return (ft_putstr_fd("fail join and free\n", 2), NULL);
		v.arg = va_arg(v.args, char *);
		v.cur_str++;
	}
	va_end(v.args);
	free(v.tabs_to_free);
	return (v.new_string);
}

/* Join an infinite amount of strings and free the wished tabs.

	The last argument should be NULL to interrupt
	the function correctly, otherwise,
	undefined outcome may happened.

	If one string is passed in argument, it behaves like strdup(s1).
	
	The string "to_free" follows the rules of the function strchar_to_strint :
	- Each numbers represent the position of each
	string that should be freed, starting
	at position zero, if the number exceeds the limits
	of the numbers of strings, they
	will be ignored.
	- The string must follow the format : "n1, n2, ..., nn".
	- If the format isn't respected, or if the string is NULL or empty, the
	string will be considered NULL and no string will be freed
	*/
char	*multi_join_n_free(char *to_free, char *s1, ...)
{
	t_mjnf	v;

	if (!s1)
		return (NULL);
	v = (t_mjnf){0};
	if (to_free && correct_format(to_free))//je verifie le format du tableau to free
	{
		v.tabs_to_free = strchar_to_strint(to_free);//je le converti en tableau d'ints
		v.tab_len = ft_strintlen(to_free);
	}
	va_start(v.args, s1);
	v.arg = va_arg(v.args, char *);
	if (!v.arg)
	{
		v.new_string = ft_strdup(s1);
		if (v.tabs_to_free && has_to_be_freed(v, &v.tab_increment))
			free(s1);
		return (va_end(v.args), free(v.tabs_to_free), v.new_string);
	}
	v.new_string = ft_strjoin(s1, v.arg);//je join
	if (v.tabs_to_free && has_to_be_freed(v, &v.tab_increment))
		free(s1);
	v.cur_str++;
	return (multi_join_n_free2(v));
}
