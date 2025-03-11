/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_absolu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:25:29 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/09 16:55:50 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* turn a number into his positive version
*/
int	ft_absolu(int nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}
