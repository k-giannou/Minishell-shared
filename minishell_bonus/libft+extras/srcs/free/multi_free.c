/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_bouble_tabs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:39:14 by marvin            #+#    #+#             */
/*   Updated: 2025/01/19 15:39:14 by marvin           ###   ########.fr       */
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

/* free an infinite number of arguments

	- The string "to_free" must follow the format : "n1, n2, ..., nn".
	- If the format isn't respected, or if the string is NULL or empty, nothing
	will be free.

	- if the number is 1, it will free a string (*str)
	- if the number is 2, it will free a board of strings (**str)

	The last argument should be NULL to interrupt the function correctly, otherwise,
	undefined outcome may happened.
*/
void	multi_free(char *to_free, ...)
{
	va_list	args;
	void	*ptrn;
	int		*tabs_to_free;
	int		i;

	tabs_to_free = NULL;
	if (to_free && correct_format(to_free))
		tabs_to_free = strchar_to_strint(to_free);
	va_start(args, to_free);
	ptrn = va_arg(args, void *);
	i = 0;
	while (ptrn)
	{
		if (tabs_to_free && tabs_to_free[i] == 1 && ptrn)
			free(ptrn);
		if (tabs_to_free && tabs_to_free[i] == 2 && (char **)ptrn)
			free_dbl_tab((char **)ptrn);
		ptrn = va_arg(args, void *);
		i++;
	}
	free(tabs_to_free);
	va_end(args);
}
