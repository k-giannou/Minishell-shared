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

/* free a splited tab
*/
void	free_dbl_tab(char **str)
{
	int	j;

	if (!str)
		return ;
	j = 0;
	while (str && str[j])
		free(str[j++]);
	if (str)
		free(str);
}
