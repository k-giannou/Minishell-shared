/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimized_argument.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:31:28 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/13 19:46:34 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_tokens(char *line, bool sgl_q, bool dbl_q, int i)
{
	int	count;

	count = 0;
	while (line[i])
	{
		while (line[i] == ' ')// 1)j'avance dans ma string jusqu'a croiser autre chose qu'un white space
			i++;
		while (line[i] && line[i] != ' ')//tant que je suis pas arriver a la fin de la ligne ou a un espace
		{
			if (line[i] == SGL_Q || line[i] == DBL_Q)//2)si mon caractere est une quote
			{
				valid_quotes(line[i++], &sgl_q, &dbl_q);
				while ((line[i] && sgl_q && line[i] != SGL_Q)
					|| (line[i] && dbl_q && line[i] != DBL_Q))//tant que je suis pas arriver a la prochaine meme quote, j'avance
					i++;
				valid_quotes(line[i++], &sgl_q, &dbl_q);
			}
			while(line[i] && line[i] != SGL_Q && line[i] != DBL_Q && line[i] != ' ')//si j'ai des characteres, quotes exclues, j'avance jusqu'a un white space ou une quote
				i++;
		}
		count++;//j'ajoute mon mot
	}
	return (count++);//sinon, je renvoie le nombre de mots
}

static char	*ft_substr2(char *line, t_minishell *mini, int len)
{
	char *str;
	int i;
	int j;

	i = 0;
	j = 0;	
	mini->sgl_q = 0;
	mini->dbl_q = 0;
	str = ft_calloc(len + 2, 1);
	if (!str)
		return (NULL);
	while (i < len)
	{
		if ((line[i] == SGL_Q || line[i] == DBL_Q) && !mini->sgl_q
			&& !mini->dbl_q)//si j'ai une quote
			valid_quotes(line[i++], &(mini->sgl_q), &(mini->dbl_q));
		if ((line[i] == SGL_Q && mini->sgl_q) || (line[i] == DBL_Q
			&& mini->dbl_q))
			valid_quotes(line[i++], &(mini->sgl_q), &(mini->dbl_q));
		else
			str[j++] = line[i++];
	}
	str[j] = 0;
	return (str);
}

char	*return_tab(int tab, int *new_i)
{
	if (tab == 0)
		return (*new_i += 2, ft_strdup("''"));
	else
		return (*new_i += 2, ft_strdup(""));
}

static char	*ft_substr_mini(char *line, t_minishell *mini, int *new_i, int tab)
{
	int	len;

	len = 0;
	(void)tab;
	if (line[0] && ((line[0] == DBL_Q && line[1] == DBL_Q)
		|| (line[0] == SGL_Q && line[1] == SGL_Q)))//si j'ai un tableau vide
		return (return_tab(tab, new_i));
	while (line[len] && line[len] != ' ')//tant que je suis pas arriver a la fin de la ligne ou a un espace
	{
		if (line[len] == SGL_Q || line[len] == DBL_Q)//si mon caractere est une quote
		{
			valid_quotes(line[len++], &(mini->sgl_q), &(mini->dbl_q));
				while ((line[len] && mini->sgl_q && line[len] != SGL_Q)
					|| (line[len] && mini->dbl_q && line[len] != DBL_Q))//tant que je suis pas arriver a la prochaine meme quote, j'avance
				len++;
			valid_quotes(line[len++], &(mini->sgl_q), &(mini->dbl_q));
		}
		while(line[len] && line[len] != SGL_Q && line[len] != DBL_Q && line[len] != ' ')//si j'ai des characteres, quotes exclues, j'avance jusqu'a un white space ou une quote
			len++;
	}
	*new_i += len;
	/* if (line[len] == ' ' && (line[len - 1] == SGL_Q || line[len - 1] == DBL_Q))
		len--; */
	return (ft_substr2(line, mini, len));//sinon, je renvoie le nombre de mots
}

static char	**split_line(char *line, char **splited_line, t_minishell *mini)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (line[i])
	{
		while (line[i] && line[i] != ' ')//tant que je suis pas arriver a la fin de la ligne ou a un espace
		{
			splited_line[j] = ft_substr_mini(line + i, mini, &i, j);
			if (!splited_line[j])
				return (free_all(NULL, splited_line), NULL);
		}
		j++;
		k = 0;
		while (line[i] == ' ')// 1)j'avance dans ma string jusqu'a croiser autre chose qu'un white space
			i++;
	}
	splited_line[j] = NULL;
	return (splited_line);
}

char	**optimised_line(char *line, t_minishell *mini)
{
	char	**splited_line;
	int i;
	int	count;

	count = count_tokens(line, 0, 0, 0);
	splited_line = ft_calloc(sizeof(char *), count + 1);
	if (!splited_line)
		return (free(line), NULL);
	i = 0;
	while (line[i] == ' ')// 1)j'avance dans ma string jusqu'a croiser autre chose qu'un white space
			i++;
	splited_line = split_line(line + i, splited_line, mini);
	free(line);
	return (splited_line);
}
