/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 20:38:24 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/08 14:34:03 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoinm(char const *s1, char const *s2)
{
	char	*new_string;
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_string = ft_calloc(len, 1);
	if (!new_string)
		return (NULL);
	while (s1[i] != '\0')
	{
		new_string[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		new_string[i++] = s2[j++];
	new_string[i] = '\0';
	return (new_string);
}

static int	init_vals(long nb, int *sign)
{
	int	i;
	int	digits;

	i = 0;
	digits = 1;
	if (nb < 0)
	{
		nb = -nb;
		*sign = 1;
	}
	while (nb >= 10)
	{
		nb /= 10;
		digits++;
	}
	i = digits + *sign;
	return (i);
}

char	*ft_itoa(int n)
{
	char	*cpy;
	long	nb;
	int		i;
	int		sign;

	nb = n;
	sign = 0;
	i = init_vals(nb, &sign);
	if (nb < 0)
		nb = -nb;
	cpy = ft_calloc(sizeof(char), i + 1);
	if (!cpy)
		return (NULL);
	if (sign == 1)
		cpy[0] = '-';
	cpy[i--] = '\0';
	while (i >= sign)
	{
		cpy[i] = nb % 10 + '0';
		nb /= 10;
		i--;
	}
	return (cpy);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup(const char *src)
{
	char	*cpy;
	int		len_src;
	int		i;

	i = 0;
	len_src = (int)ft_strlen(src);
	cpy = (char *)ft_calloc(sizeof(char), (len_src + 1));
	if (!cpy)
		return (NULL);
	while (src[i] != '\0')
	{
		cpy[i] = src[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
