/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimized_argument.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:31:28 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/08 18:13:10 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	valid_quotes(char c, bool *single_quote, bool *double_quote)
{
	if (!(*single_quote) && !(*double_quote))
	{
		if (c == SGL_Q)
			(*single_quote) = 1;
		else if (c == DBL_Q)
			(*double_quote) = 1;
	}
	else if ((*single_quote) || (*double_quote))
	{
		if (c == SGL_Q && (*single_quote) && !(*double_quote))
			(*single_quote) = 0;
		else if (c == DBL_Q && (*double_quote) && !(*single_quote))
			(*double_quote) = 0;
	}
}

static int	count_tokens(char *line, bool single_quote, bool double_quote, int i)
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
				valid_quotes(line[i++], &single_quote, &double_quote);
				while ((line[i] && single_quote && line[i] != SGL_Q)
					|| (line[i] && double_quote && line[i] != DBL_Q))//tant que je suis pas arriver a la prochaine meme quote, j'avance
					i++;
				valid_quotes(line[i++], &single_quote, &double_quote);
			}
			while(line[i] && line[i] != SGL_Q && line[i] != DBL_Q && line[i] != ' ')//si j'ai des characteres, quotes exclues, j'avance jusqu'a un white space ou une quote
				i++;
		}
		count++;//j'ajoute mon mot
	}
	if (single_quote || double_quote)//si les quotes se ferment pas correctement, erreur
		return (ft_fprintf(2, "Error : quotes aren't closed properly\n"), free(line), -1);
	return (count++);//sinon, je renvoie le nombre de mots
}

static char	*ft_substr(char *line, t_minishell *mini, int i, int j, int *new_i)
{
	int	len;
	char *str;

	len = 0;
	if (line[0] && ((line[0] == DBL_Q && line[1] == DBL_Q)
		|| (line[0] == SGL_Q && line[1] == SGL_Q)))//si j'ai un tableau vide
		return (*new_i += 2, str = ft_calloc(1, 1), str);
	while (line[len] && line[len] != ' ')//tant que je suis pas arriver a la fin de la ligne ou a un espace
	{
		if (line[len] == SGL_Q || line[len] == DBL_Q)//si mon caractere est une quote
		{
			valid_quotes(line[len++], &(mini->single_quote), &(mini->double_quote));
				while ((line[len] && mini->single_quote && line[len] != SGL_Q)
					|| (line[len] && mini->double_quote && line[len] != DBL_Q))//tant que je suis pas arriver a la prochaine meme quote, j'avance
				len++;
			valid_quotes(line[len++], &(mini->single_quote), &(mini->double_quote));
		}
		while(line[len] && line[len] != SGL_Q && line[len] != DBL_Q && line[len] != ' ')//si j'ai des characteres, quotes exclues, j'avance jusqu'a un white space ou une quote
			len++;
	}
	*new_i += len;
	if (line[len] == ' ' && (line[len - 1] == SGL_Q || line[len - 1] == DBL_Q))
		len--;
	str = ft_calloc(len + 1, 1);
	if (!str)
		return (NULL);
	while (i < len)
	{
		while (line[i] == SGL_Q || line[i] == DBL_Q)//si j'ai une quote
			i++;
		str[j++] = line[i++];
	}
	str[j] = 0;
	return (str);//sinon, je renvoie le nombre de mots
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
			splited_line[j] = ft_substr(line + i, mini, 0, 0, &i);
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

	splited_line = ft_calloc(sizeof(char *), count_tokens(line, 0, 0, 0) + 1);
	if (!splited_line)
		return (free(line), NULL);
	i = 0;
	while (line[i] == ' ')// 1)j'avance dans ma string jusqu'a croiser autre chose qu'un white space
			i++;
	splited_line = split_line(line + i, splited_line, mini);
	free(line);
	return (splited_line);
}
