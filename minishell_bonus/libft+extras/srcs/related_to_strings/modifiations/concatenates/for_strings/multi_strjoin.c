/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_strjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiannou <kgiannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:07:25 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/21 12:42:36 by kgiannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* join an infinite amount of strings,
the last argument should be NULL to interrupt
the function correctly, otherwise, undefined outcome may happened.

if the function has only one string, it behave like strdup(s1).
*/
char	*multi_join(char *s1, ...)
{
	va_list	args;
	char	*arg;
	char	*new_string;

	if (!s1)
		return (NULL);
	va_start(args, s1);
	arg = va_arg(args, char *);
	if (!arg)
		return (va_end(args), ft_strdup(s1));
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
