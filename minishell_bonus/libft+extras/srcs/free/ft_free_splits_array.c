/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_splits_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiannou <kgiannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:24:32 by locagnio          #+#    #+#             */
/*   Updated: 2025/04/06 18:28:50 by kgiannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* free an array of splits and set it to NULL.
*/
void	ft_free_splits_array(char ****cmd_s)
{
	int	j;

	if (!(*cmd_s) || !(*cmd_s)[0])
		return ;
	j = 0;
	while ((*cmd_s)[j])
		free_dbl_tab((*cmd_s)[j++]);
	if ((*cmd_s))
		free((*cmd_s));
	(*cmd_s) = NULL;
}
