/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 20:17:08 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/26 16:25:19 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_export(t_env *v, bool sign, bool inside)
{
	int		i;

	while (v != NULL)
	{
		printf("declare -x ");
		i = 0;
		while (v->data[i])
		{
			if (v->data[i] == '=' && !inside)
			{
				sign = true;
				inside = true;
				printf("%c", v->data[i++]);
				printf("\"");
			}
			printf("%c", v->data[i++]);
		}
		if (v->data[i] == '\0' && sign)
			printf("\"");
		printf("\n");
		v = v->next;
		sign = false;
		inside = false;
	}
}

void	print_list(t_env *L)
{
	if (!L)
		printf("(null)");
	while (L)
	{
		printf("%s\n", L->data);
		L = L->next;
	}
}
