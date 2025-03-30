/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:45:29 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/30 23:57:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*host_dup(char *name)
{
	char			*dest;
	int				i;
	int				j;
	int				k;
	unsigned char	unicode_heart[4];

	i = ft_strlen(name);
	unicode_heart[0] = 0xF0;
	unicode_heart[1] = 0x9F;
	unicode_heart[2] = 0x8C;
	unicode_heart[3] = 0xB4;
	dest = (char *)ft_calloc(sizeof(char), i + 20);
	if (!dest)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	while (j < 4)
		dest[k++] = unicode_heart[j++];
	while (name[i] != '.' && name[i] != '\0')
		dest[k++] = name[i++];
	dest[k++] = ':';
	dest[k] = '\0';
	return (dest);
}

char	*hostname(void)
{
	int		fd;
	int		bytes;
	char	hostname[50];

	bytes = 0;
	ft_bzero(hostname, 50);
	fd = open(HOSTNAME, O_RDONLY);
	if (fd != -1)
	{
		bytes = read(fd, hostname, 9);
		if (bytes != -1)
			return (host_dup(hostname));
	}
	close(fd);
	return (NULL);
}

void	init_user(t_minishell *mini)
{
	mini->user.hostname = NULL;
	mini->user.hostname = hostname();
	mini->user.name = NULL;
	mini->user.name = getenv("USER");
	mini->user.final = ft_strjoin_n_free(mini->user.name, mini->user.hostname,
			2);
}

long	len_list(t_env *list)
{
	long	len;

	if (!list)
		return (0);
	len = 0;
	while (list)
	{
		len++;
		list = list->next;
	}
	return (len);
}

int	ft_strrchr(const char *s, int c)
{
	int	len;

	len = (int)ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == (char)c)
			return (len);
		len--;
	}
	return (0);
}
