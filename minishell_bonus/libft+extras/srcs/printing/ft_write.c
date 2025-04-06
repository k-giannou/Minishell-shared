/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:53:35 by locagnio          #+#    #+#             */
/*   Updated: 2025/04/06 14:56:02 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* because searching for the lenght of the string is annoying.
*/
int	ft_write(int fd, char *s)
{
	return (write(fd, s, ft_strlen(s)));
}
