/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_multi_char_cmp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:34:04 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/14 18:23:53 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* return a char if a comparison was successful, else it
	returns 0.

	- if n < 0, the function will take a lenght for each string in
	the following format "s1, s2, n_s2, s3, n_s3,..., sn, n_sn".
	- else if n = 0, the function will behave like a multicmp.
	- else, n will be applied for every string.

	the last argument should be NULL, otherwise, the function may have an undefined
	behavior.
*/
char	get_multi_char_cmp(int s1, ...)
{
	int	arg;
	va_list	args;

	if (!ft_isascii(s1) || !s1)
		return (0);
	va_start(args, s1);
	arg = va_arg(args, int);
	while (!ft_isascii(arg))
			arg = va_arg(args, int);
	while (arg)
	{
		if (s1 == arg)
			return (va_end(args), arg);
		else
			arg = va_arg(args, int);
		while (!ft_isascii(arg))
			arg = va_arg(args, int);
	}
	va_end(args);
	return (0);
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