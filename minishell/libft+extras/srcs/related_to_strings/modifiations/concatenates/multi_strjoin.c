/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_strjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:07:25 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/08 21:00:50 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* join an infinite amount of strings */
char	*multi_join(char *s1,...)
{
	va_list	args;
	char	*arg;
	char	*new_string;

	va_start(args, s1);
	arg = va_arg(args, char *);
	if (!s1 && !arg)
		return (va_end(args), NULL);
	new_string = ft_strjoin(s1, arg);
	if (!new_string)
			return (ft_putstr_fd("fail join\n", 2), NULL);
	arg = va_arg(args, char *);
	while (arg)
	{
		new_string = ft_strjoin_n_free(new_string, arg, 1);
		if (!new_string)
			return (ft_putstr_fd("fail join and free\n", 2), NULL);
		arg = va_arg(args, char *);
	}
	va_end(args);
	return (new_string);
}
