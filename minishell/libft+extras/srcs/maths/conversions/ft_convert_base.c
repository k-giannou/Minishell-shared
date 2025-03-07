/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:58:28 by locagnio          #+#    #+#             */
/*   Updated: 2025/01/18 16:38:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

/* converts a string of numbers on a certain base into another base */

static void	error_msg(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

static int	ft_error(char *base)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if ((int)ft_strlen(base) <= 1)
		error_msg(RED"Error : invalid base\n"RESET);
	if (base[i] == ' ' || base[i] == '-' || base[i] == '+'
		|| (base[i] >= 9 && base[i] <= 13))
		error_msg(RED"Error : white spaces in base\n"RESET);
	while (i <= (int)ft_strlen(base))
	{
		while (j <= (int)ft_strlen(base))
		{
			if (base[i] == base[j])
				error_msg(RED"Error : duplicates in base\n"RESET);
			if (base[j] == ' ' || base[j] == '-' || base[j] == '+'
				|| (base[j] >= 9 && base[j] <= 13))
				error_msg(RED"Error : white spaces in base\n"RESET);
			j++;
		}
		i++;
		j = i + 1;
	}
	return (0);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	if (!ft_error(base_from) && !ft_error(base_to))
		return (ft_itoa_base(ft_atoi_base(nbr, base_from), base_to));
	return (NULL);
}

/* #include <stdio.h>

int	main(void)
{
	printf("nombre attendu : 0\n\tretour : %s\n\n", ft_convert_base("0",\
	 "0123456789", "0123456789ABCDEF"));
	printf("nombre attendu : 9\n\tretour : %s\n\n", ft_convert_base("9",\
	 "0123456789", "0123456789ABCDEF"));
	printf("nombre attendu : -9\n\tretour : %s\n\n", ft_convert_base("-9",\
	 "0123456789", "0123456789ABCDEF"));
	printf("nombre attendu : D\n\tretour : %s\n\n", ft_convert_base("13",\
	 "0123456789", "0123456789ABCDEF"));
	printf("nombre attendu : -F\n\tretour : %s\n\n", ft_convert_base("-15",\
	 "0123456789", "0123456789ABCDEF"));
	printf("nombre attendu : 1FBC\n\tretour : %s\n\n", ft_convert_base("8124",\
	 "0123456789", "0123456789ABCDEF"));
	return (0);
} */
