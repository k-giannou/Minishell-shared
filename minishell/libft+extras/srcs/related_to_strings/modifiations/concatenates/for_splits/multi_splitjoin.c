/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_splitjoin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiannou <kgiannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:07:25 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/21 12:31:28 by kgiannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* join an infinite amount of splits,
the last argument should be NULL to interrupt
the function correctly, otherwise, undefined outcome may happened.

if the function has only one split, it behave like splitdup(s1).
*/
char	**multi_splitjoin(char **s1, ...)
{
	va_list	args;
	char	**arg;
	char	**new_split;

	if (!s1)
		return (NULL);
	va_start(args, s1);
	arg = va_arg(args, char **);
	if (!arg)
		return (va_end(args), ft_splitdup(s1));
	new_split = ft_splitjoin((const char **)s1, (const char **)arg);
	if (!new_split)
		return (ft_putstr_fd("fail join\n", 2), NULL);
	arg = va_arg(args, char **);
	while (arg)
	{
		new_split = ft_splitjoin_n_free(new_split, arg, 1);
		if (!new_split)
			return (ft_putstr_fd("fail join and free\n", 2), NULL);
		arg = va_arg(args, char **);
	}
	va_end(args);
	return (new_split);
}
