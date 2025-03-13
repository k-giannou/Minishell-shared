/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_multi_cmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:34:04 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/13 18:38:43 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* return a string if a comparison was successful, else it
	returns NULL.

	- if n < 0, the function will take a lenght for each string in
	the following format "s1, s2, n_s2, s3, n_s3,..., sn, n_sn".
	- else if n = 0, the function will behave like a multicmp.
	- else, n will be applied for every string.

	the last argument should be NULL, otherwise, the function may have an undefined
	behavior.
*/
char	*get_multi_cmp(const char *s1, ...)
{
	const char	*arg;
	va_list		args;

	if (!s1)
		return (NULL);
	va_start(args, s1);
	arg = va_arg(args, const char *);
	while (arg)
	{
		if (!ft_strcmp(s1, arg))
			return (va_end(args), (char *)arg);
		else
			arg = va_arg(args, const char *);
		
	}
	va_end(args);
	return (NULL);
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