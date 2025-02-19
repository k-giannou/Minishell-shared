/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:45:29 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/19 20:53:10 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*host_dup(char *name)
{
	char	*dest;
	int	i;
	int	k;

	i = ft_strlen(name);
	dest = (char *)ft_calloc(sizeof(char), i + 2);
	if (!dest)
		return (NULL);
	i = 0;
	k = 1;
	dest[0] = '@';
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
	mini->user.final = ft_strjoin_n_free(mini->user.name, mini->user.hostname, 2);
	//printf("%s\n", mini->user.final);
}

long	len_list(t_env *list)
{
	long	len;

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
