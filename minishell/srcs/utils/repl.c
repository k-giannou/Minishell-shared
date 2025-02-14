#include "../includes/minishell.h"

char	*ftstrdup(char *src)
{
	char	*dest;
	int	i;

	i = 0;
	while (src[i])
		i++;
	dest = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (src[i])
	{
	   dest[i] = src[i];
	   i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_charset(int c)
{
	char	set[] = " $  ' ";
	int i;
	
	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i++] || c == '\0' || c == '\"')
			return (1);
	}
	return (0);
}

void	init_v(t_variables v)
{
	v.dbl_quote = false;
	v.quote_sum = 0;
	v.i = 0;
	v.k = 0;
	v.t = 0;
}

void	handle_single(t_variables *v, char *str)
{
	v->line[v->k++] = str[v->i++];//copys openning '
	while (str[v->i] != '\'' && str[v->i] != '\0')
		v->line[v->k++] = str[v->i++];
	v->line[v->k++] = str[v->i++];//copys closing '
}

void	change_bools(t_variables *v, char *str)
{
	v->line[v->k++] = str[v->i++];
	v->quote_sum++;
	if (v->quote_sum % 2 == 0)
		v->dbl_quote = false;//not inside double quote
	else
		v->dbl_quote = true;
}

void	search_and_change(t_variables *v, char *str, t_minishell *mini, t_env *current)
{
	//t_env	*current;
	char	*dest;

	current = mini->env;
	v->i++;//we pass $
	v->t = 0;
	current = mini->env;
	while (ft_isalpha(str[v->i]) || ft_isdigit(str[v->i]) || str[v->i] == '_')
		v->to_search[v->t++] = str[v->i++];
	v->to_search[v->t++] = '\0';//++ becuse we need it later
	dest = ftstrdup(v->to_search);
	while (current)
	{
		if (ft_strncmp(dest, current->data, ft_strlen(dest)) == 0)
		{
			while (current->data[v->t] != '\0')
				v->line[v->k++] = current->data[v->t++];
			break ;
		}
		current = current->next;
	}
	free (dest);
	dest = NULL;
}

void	start_replace(t_variables *v, char *str, t_minishell *mini, t_env *current)
{
	while (str[v->i] != '\0')
    {
		
	 	if (str[v->i] == '\'' && (!v->dbl_quote))//when it founds ' , it conitinues copy exaclty until it founds the other ' .
			handle_single(v, str);
		else if (str[v->i]== '\"')//check the double quotes and print them
			change_bools(v, str);
		else if (str[v->i] == '$')//when finds $ , check the rules are needed to see if do replace
		{
			if (str[v->i + 1] == '\0' || str[v->i + 1] == 32 || str[v->i + 1] == '$')
					v->line[v->k++] = str[v->i++];
			else if (str[v->i + 1] == '\"' && v->dbl_quote)//if inside dbl quotes we copy the $
				v->line[v->k++] = str[v->i++];
			else if ((str[v->i + 1] == '\"' || str[v->i + 1] == '\'') && (!v->dbl_quote))//if outside dbl we ignore it
				v->i++;
		 	else if (ft_isalpha(str[v->i + 1]) || ft_isdigit(str[v->i + 1]) || str[v->i + 1] == '_')
					search_and_change(v, str, mini, current);
			else
				v->line[v->k++] = str[v->i++];
		}
		else 		
			v->line[v->k++] = str[v->i++];
	}
}

char    *replace_var(t_minishell *mini, char *str)
{
    t_env	*current;
	t_variables v;

	if (!str)
		return (printf("exit\n"), exit(1), NULL);
	v = mini->vars;
	init_v(v);
    current = mini->env;
    if (!current)
        return (NULL);
	else 
		start_replace(&v, str, mini, current);
	v.line[v.k] = '\0';
	free(str);
	return (ftstrdup(v.line));
}
