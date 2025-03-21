/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_multi_cmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiannou <kgiannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:34:04 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/21 12:29:18 by kgiannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* Compares an infinite amout of characters.

	Return 0 if a comparison was successful, else it returns 1, the last argument
	should be NUL-terminated.
*/
int	char_multi_cmp(int s1, ...)
{
	int		arg;
	va_list	args;

	if (!ft_isascii(s1) || !s1)
		return (1);
	va_start(args, s1);
	arg = va_arg(args, int);
	while (!ft_isascii(arg))
		arg = va_arg(args, int);
	while (arg)
	{
		if (s1 == arg)
			return (va_end(args), 0);
		else
			arg = va_arg(args, int);
		while (!ft_isascii(arg))
			arg = va_arg(args, int);
	}
	va_end(args);
	return (1);
}

/* #include <stdio.h>

int	main(void)
{
	char s1[] = "Hello World";
	char s2[] = "Hello World";
	unsigned int n = 13;

	printf("%d\n", ft_strncmp(s1, s2, n));
	return (0);
} */