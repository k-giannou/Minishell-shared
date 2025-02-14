/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:19:00 by locagnio          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/02/14 16:38:49 by locagnio         ###   ########.fr       */
=======
/*   Updated: 2025/02/14 16:25:36 by kgiannou         ###   ########.fr       */
>>>>>>> 896545fe673c7ad86259673a24966e253da81015
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	valid_quotes(char c, bool *sgl_q, bool *dbl_q)
{
	if (!(*sgl_q) && !(*dbl_q))
	{
		if (c == SGL_Q)
			(*sgl_q) = 1;
		else if (c == DBL_Q)
			(*dbl_q) = 1;
	}
	else if ((*sgl_q) || (*dbl_q))
	{
		if (c == SGL_Q && (*sgl_q) && !(*dbl_q))
			(*sgl_q) = 0;
		else if (c == DBL_Q && (*dbl_q) && !(*sgl_q))
			(*dbl_q) = 0;
	}
}

int	check_quotes(char *str)
{
	int i;
	bool sgl_q;
	bool dbl_q;

	if (!str)
		return (0);
	add_history(str);
	i = 0;
	sgl_q = 0;
	dbl_q = 0;
	while (str[i])
		valid_quotes(str[i++], &sgl_q, &dbl_q);
	if (sgl_q || dbl_q)
	{
		ft_fprintf(2, "Error : quotes aren't closed properly\n");
		free(str);
		return (1);
	}
	return (0);
}

t_env	*add_at(t_env *L, char *data, int pos)
{
	t_env	*prec;
	t_env	*cur;
	int		i;
	t_cell	*cell;

	cur = L;
	cell = create_cell(data);
	if (!cell)
		return (NULL);
	if (!L)
		return (cell);
	else if (pos == 0)
	{
		cell->next = L;
		return (cell);
	}
	i = 0;
	while (i++ < pos)
	{
		prec = cur;
		cur = cur->next;
	}
	prec->next = cell;
	cell->next = cur;
	return (L);
}

t_env	*ft_envdup(t_env *src)
{
	t_env	*cpy;
	t_env	*tmp;
	int		i;

	tmp = src;
	i = 0;
	cpy = NULL;
	while (tmp)
	{
		cpy = add_at(cpy, ft_strdup(tmp->data), i);
		i++;
		tmp = tmp->next;
	}
	return (cpy);
}

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
<<<<<<< HEAD
	while (name[i] != '.')
=======
	while (name[i] != '.' && name[i] != '\0')
>>>>>>> 896545fe673c7ad86259673a24966e253da81015
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