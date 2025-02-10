#include "../includes/minishell.h"

typedef struct s_variables
{
	char	line[70000];//we check the str and we copy char by char in like, except it needs replace
	char	to_search[70000];
    int	i;
	int	k;
	int	t;
	bool dbl_quote;
	int	quote_sum;
} t_variables ;

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

char    *replace_var(t_minishell *mini, char *str)
{
    t_env	*current;
	t_variables v;

	char	*dest;
	v.dbl_quote = false;
	v.quote_sum = 0;
    current = mini->env;
    if (!current)
        return (NULL);
    v.i = 0;
	v.k = 0;
    while (str[v.i] != '\0')
    {
		
	 	if (str[v.i] == '\'' && (!v.dbl_quote))//when it founds ' , it conitinues copy exaclty until it founds the other ' .
		{
			v.line[v.k++] = str[v.i++];//copys openning '
			while (str[v.i] != '\'' && str[v.i] != '\0')
				v.line[v.k++] = str[v.i++];
			v.line[v.k++] = str[v.i++];//copys closing '
		}
		else if (str[v.i]== '\"')//check the double quotes and print them
		{
			v.line[v.k++] = str[v.i++];
			v.quote_sum++;
			if (v.quote_sum % 2 == 0)
				v.dbl_quote = false;//not inside double quote
			else
				v.dbl_quote = true;
		}
		else if (str[v.i] == '$')//when finds $ , check the rules are needed to see if do replace
		{
			if (str[v.i + 1] == '\0' || str[v.i + 1] == 32 || str[v.i + 1] == '$')
					v.line[v.k++] = str[v.i++];
			else if (str[v.i + 1] == '\"' && v.dbl_quote)//if inside dbl quotes we copy the $
				v.line[v.k++] = str[v.i++];
			else if (str[v.i + 1] == '\"' && (!v.dbl_quote))//if outside dbl we ignore it
				v.i++;
		 	else// if (str[i + 1] == '\"' && ((quote_sum % 2 == 1)))//if outside
			{
					v.i++;//we pass $
					v.t = 0;
				 	current = mini->env;
					while (!ft_charset(str[v.i]))
						v.to_search[v.t++] = str[v.i++];
					v.to_search[v.t++] = '\0';//++ becuse we need it later
					dest = ftstrdup(v.to_search);
					while (current)
					{
						if (ft_strncmp(dest, current->data, ft_strlen(dest)) == 0)
						{
							while (current->data[v.t] != '\0')
								v.line[v.k++] = current->data[v.t++];
							break ;
						}
						current = current->next;
					}
					free (dest);
					dest = NULL;
			}
		}
		else 		
			v.line[v.k++] = str[v.i++];
	}
	v.line[v.k] = '\0';
	free(str);
	return (ftstrdup(v.line));
}
