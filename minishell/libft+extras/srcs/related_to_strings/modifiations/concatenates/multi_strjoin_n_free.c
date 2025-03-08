/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_strjoin_n_free.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:07:25 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/08 21:02:03 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

static bool correct_format(char *str_char)
{
	int i;

	i = 0;
	while (str_char[i])
	{
		if (ft_isnum(str_char[i]))
			i++;
		else if(ft_strcmp(str_char + i, ", ") && i != 0)
			i+= 2;
		else
			return (0);
	}
	return (1);
}

char *multi_join_n_free2(char *new_string, int *tabs_to_free, va_list args)
{
	int i;
	char *arg;

	arg = va_arg(args, char *);
	i = 2;
	while (arg)
	{
		new_string = ft_strjoin_n_free(new_string, arg, 1);
		if (tabs_to_free && tabs_to_free[i])
			free(arg);
		if (!new_string)
			return (ft_putstr_fd("fail join and free\n", 2), NULL);
		arg = va_arg(args, char *);
	}
	va_end(args);
	free(tabs_to_free);
	return (new_string);
}

/* Join an infinite amount of strings and free the wished tabs.
	The string "to_free" take only the position of the tabs to free, separated
	by a ",", if theses formating conditions aren't take in count, or if the
	parameter is NULL or empty, nothing will be freed
	
	The converted string "to_free" follows the rules of the function strchar_to_strint :
	- The string must follow the following format : "n1, n2, ..., nn".
	- If the format isn't respected, or if the string is NULL or empty, the
	function returns NULL */
char	*multi_join_n_free(char *to_free, char *s1, ...)
{
	char	*arg;
	va_list	args;
	char	*new_string;
	int 	*tabs_to_free;

	if (!to_free || !correct_format(to_free))//je verifie le format du tableau to free
		tabs_to_free = NULL;
	else
		tabs_to_free = strchar_to_strint(to_free);//je le converti en tableau d'ints
	va_start(args, s1);
	arg = va_arg(args, char *);
	if (!s1 && !arg)//si les deux arguments sont NULL
		return (va_end(args), NULL);//je return NULL
	new_string = ft_strjoin(s1, arg);//je join
	if (tabs_to_free && tabs_to_free[0])
		free(s1);
	if (tabs_to_free && tabs_to_free[1])
		free(arg);
	if (!new_string)
			return (ft_putstr_fd("fail join\n", 2), NULL);
	return (multi_join_n_free2(new_string, tabs_to_free, args));
}
