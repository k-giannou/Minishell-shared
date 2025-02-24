/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimized_argument.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:31:28 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/20 16:39:26 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	if_pipes_or_redirs(char *line, int *i, int *count)
{
	if (line[*i] == '<' || line[*i] == '>' || line[*i] == '|')//si j'ai des redirections ou des pipes
	{
		(*count)++;//je compte comme un mot les characteres d'avant
		while (line[*i + 1] == '<' || line[*i + 1] == '>'
			|| line[*i + 1] == '|')//tant que j'ai une redirection ou un pipe, je passe
			(*i)++;
		if (line[*i + 1] != ' ')//si j'ai encore des characteres apres je compte les redirections ou les pipes comme un mot et je continue
			(*count)++;
	}
	(*i)++;
}

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
			while(line[i] && line[i] != SGL_Q && line[i] != DBL_Q
				&& line[i] != ' ')//si j'ai des characteres, quotes exclues, j'avance jusqu'a un white space ou une quote
				if_pipes_or_redirs(line, &i, &count);
		}
		count++;//j'ajoute mon mot
	}
	return (count++);//sinon, je renvoie le nombre de mots
}

static char	*ft_substr2(char *line, t_minishell **mini, int len)
{
	char *str;
	int i;
	int j;

	i = 0;
	j = 0;	
	(*mini)->sgl_q = 0;
	(*mini)->dbl_q = 0;
	str = ft_calloc(len + 2, 1);
	if (!str)
		return (NULL);
	while (i < len)
	{
		if ((line[i] == SGL_Q || line[i] == DBL_Q) && !(*mini)->sgl_q
			&& !(*mini)->dbl_q)//si j'ai une quote
			valid_quotes(line[i++], &((*mini)->sgl_q), &((*mini)->dbl_q));
		if ((line[i] == SGL_Q && (*mini)->sgl_q) || (line[i] == DBL_Q
			&& (*mini)->dbl_q))
			valid_quotes(line[i++], &((*mini)->sgl_q), &((*mini)->dbl_q));
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

static char	*ft_substr_mini(char *line, t_minishell **mini, int *new_i, int tab)
{
	int	len;

	len = 0;
	if (line[0] && ((line[0] == DBL_Q && line[1] == DBL_Q)
		|| (line[0] == SGL_Q && line[1] == SGL_Q)))//si j'ai un tableau vide
		return ((*mini)->pipes_redirs[tab] = return_tab(tab, new_i), return_tab(tab, new_i));
	if (line[len] == '<' || line[len] == '>' || line[len] == '|')
		while (line[len] == '<' || line[len] == '>' || line[len] == '|')//tant que j'ai une redirection ou un pipe, je passe
				len++;
	else
	{
		while (line[len] && line[len] != ' ' && line[len] != '<' && line[len] != '>'
				&& line[len] != '|')//tant que je suis pas arriver a la fin de la ligne ou a un espace
		{
			if (line[len] == SGL_Q || line[len] == DBL_Q)//si mon caractere est une quote
			{
				valid_quotes(line[len++], &((*mini)->sgl_q), &((*mini)->dbl_q));
					while ((line[len] && (*mini)->sgl_q && line[len] != SGL_Q)
						|| (line[len] && (*mini)->dbl_q && line[len] != DBL_Q))//tant que je suis pas arriver a la prochaine meme quote, j'avance
					len++;
				valid_quotes(line[len++], &((*mini)->sgl_q), &((*mini)->dbl_q));
			}
			while(line[len] && line[len] != SGL_Q && line[len] != DBL_Q
				&& line[len] != ' ' && line[len] != '<' && line[len] != '>'
				&& line[len] != '|')//si j'ai des characteres, quotes exclues, j'avance jusqu'a un white space ou une quote
				len++;
		}
	}
	*new_i += len;
	(*mini)->pipes_redirs[tab] = ft_substr_with_quotes(line, *mini, len);
	return (ft_substr2(line, mini, len));//sinon, je renvoie le nombre de mots
}

void	split_line(char *line, t_minishell **mini)
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
			(*mini)->tokens[j] = ft_substr_mini(line + i, mini, &i, j);
			if (!(*mini)->tokens[j])
				return (free_all(*mini, "tabs"));
			else if ((line[i] == '<' || line[i] == '>' || line[i] == '|')
				|| ((*mini)->tokens[j][0] == '<' || (*mini)->tokens[j][0] == '>'
				|| (*mini)->tokens[j][0] == '|'))
				break ;
		}
		j++;
		k = 0;
		while (line[i] == ' ')// 1)j'avance dans ma string jusqu'a croiser autre chose qu'un white space
			i++;
	}
	(*mini)->tokens[j] = NULL;
	(*mini)->pipes_redirs[j] = NULL;
}

void	optimised_line(char *line, t_minishell **mini)
{
	int i;
	int	count;

	count = count_tokens(line, 0, 0, 0);
	(*mini)->tokens = malloc(sizeof(char *) * (count + 1));
	(*mini)->pipes_redirs = malloc(sizeof(char *) * (count + 1));
	if (!(*mini)->tokens || !(*mini)->pipes_redirs)
		return (free(line));
	i = 0;
	while (line[i] == ' ')// 1)j'avance dans ma string jusqu'a croiser autre chose qu'un white space
			i++;
	split_line(line + i, mini);
	free(line);
}
