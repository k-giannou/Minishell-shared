/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimized_argument.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:31:28 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/07 20:35:13 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	valid_quotes(char c, bool *single_quote, bool *double_quote)
{
	if (!(*single_quote) && !(*double_quote))
	{
		if (c == '\'')
			(*single_quote) = 1;
		else if (c == '"')
			(*double_quote) = 1;
	}
	else if ((*single_quote) || (*double_quote))
	{
		if (c == '\'' && (*single_quote) && !(*double_quote))
			(*single_quote) = 0;
		else if (c == '"' && (*double_quote) && !(*single_quote))
			(*double_quote) = 0;
	}
}

static int	count_tokens(char *line, bool single_quote, bool double_quote)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		while (line[i] == ' ')// 1)j'avance dans ma string jusqu'a croiser autre chose qu'un white space
			i++;
		while (line[i] && line[i] != ' ')//tant que je suis pas arriver a la fin de la ligne ou a un espace
		{
			if (line[i] == '\'' || line[i] == '"')//2)si mon caractere est une quote
			{
				valid_quotes(line[i++], &single_quote, &double_quote);
				while ((line[i] && single_quote && line[i] != '\'')
					|| (line[i] && double_quote && line[i] != '"'))//tant que je suis pas arriver a la prochaine meme quote, j'avance
					i++;
				valid_quotes(line[i++], &single_quote, &double_quote);
			}
			while(line[i] && line[i] != '\'' && line[i] != '"' && line[i] != ' ')//si j'ai des characteres, quotes exclues, j'avance jusqu'a un white space ou une quote
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
	if (line && line[0] == 0)//si j'ai un tableau vide
		return (str = malloc(1), str[0] = 0, str);
	while (line[len] && line[len] != ' ')//tant que je suis pas arriver a la fin de la ligne ou a un espace
	{
		if (line[len] == '\'' || line[len] == '"')//si mon caractere est une quote
		{
			valid_quotes(line[len++], &(mini->single_quote), &(mini->double_quote));
				while ((line[len] && mini->single_quote && line[len] != '\'')
					|| (line[len] && mini->double_quote && line[len] != '"'))//tant que je suis pas arriver a la prochaine meme quote, j'avance
				len++;
			valid_quotes(line[len], &(mini->single_quote), &(mini->double_quote));
			if (line[len] && line[len + 1] && line[len + 1] != ' ')//si j'ai pas d'espaces apres les quotes
				len++;
		}
		while(line[len] && line[len] != '\'' && line[len] != '"' && line[len] != ' ')//si j'ai des characteres, quotes exclues, j'avance jusqu'a un white space ou une quote
			len++;
	}
	*new_i += len;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	while (i < len)
	{
		while (line[i] == '\'' || line[i] == '"')//si j'ai une quote
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
				return (free_dbl_tab(splited_line), free(line), NULL);
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

	splited_line = malloc(sizeof(char *) * count_tokens(line, 0, 0) + 1);
	if (!splited_line)
		return (NULL);
	i = 0;
	while (line[i] == ' ')// 1)j'avance dans ma string jusqu'a croiser autre chose qu'un white space
			i++;
	splited_line = split_line(line + i, splited_line, mini);
	return (splited_line);
}
