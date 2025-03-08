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
	WARNING : if one of the arguments exceed one "*", it won't free the other
	pointers contained in this pointer */
void	multi_free(char *to_free, ...)
{
	va_list	args;
	void	*ptrn;
	int		*tabs_to_free;
	int		i;

	if (!to_free || !correct_format(to_free))//je verifie le format du tableau to free
		tabs_to_free = NULL;
	else
		tabs_to_free = strchar_to_strint(to_free);//je le converti en tableau d'ints
	va_start(args, to_free);
	ptrn = va_arg(args, void *);
	i = 0;
	while (ptrn)
	{
		if (!tabs_to_free[i])
			free(ptrn);
		if (tabs_to_free[i])
			free_dbl_tab((char **)ptrn);
		ptrn = va_arg(args, void *);
	}
	free(tabs_to_free);
	va_end(args);
}
