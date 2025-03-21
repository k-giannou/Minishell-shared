/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_multi_ncmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiannou <kgiannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:34:04 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/21 13:25:33 by kgiannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* return 0 if a comparison of n charaters was successful, else it returns 1
*/
int	str_multi_ncmp(size_t n, const char *s1, ...)
{
	const char	*arg;
	va_list		args;

	va_start(args, s1);
	arg = va_arg(args, const char *);
	while (arg)
	{
		if (!ft_strncmp(s1, arg, n))
			return (va_end(args), 0);
		else
			arg = va_arg(args, const char *);
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