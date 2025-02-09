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

char    *replace_var(t_minishell *mini, char *str)//it must take quotes that open and close correctly
{
    t_env	*current;
	char	line[70000];//we check the str and we copy char by char in like, except it needs replace
	char	to_search[70000];
    int	i;
	int	k;
	int	t;
	char	*dest;
	bool dbl_quote = false;
	int	quote_sum = 0;
	
    current = mini->env;
    if (!current)
        return (NULL);
    i = 0;
	k = 0;
    while (str[i] != '\0')
    {
		
	 	if (str[i] == '\'' && (!dbl_quote))//when it founds ' , it conitinues copy exaclty until it founds the other ' .
		{
			line[k++] = str[i++];//copys openning '
			while (str[i] != '\'' && str[i] != '\0')
				line[k++] = str[i++];
			line[k++] = str[i++];//copys closing '
		}
		else if (str[i]== '\"')//check the double quotes and print them
		{
			line[k++] = str[i++];
			quote_sum++;
			if (quote_sum % 2 == 0)
				dbl_quote = false;//not inside double quote
			else
				dbl_quote = true;
		}
		else if (str[i] == '$')//when finds $ , check the rules are needed to see if do replace
		{
			if (str[i + 1] == '\0' || str[i + 1] == 32 || str[i + 1] == '$')
					line[k++] = str[i++];
			else if (str[i + 1] == '\"' && dbl_quote)//if inside dbl quotes we copy the $
				line[k++] = str[i++];
			else if (str[i + 1] == '\"' && (!dbl_quote))//if outside dbl we ignore it
				i++;
		 	else// if (str[i + 1] == '\"' && ((quote_sum % 2 == 1)))//if outside
			{
					i++;//we pass $
					t = 0;
				 	current = mini->env;
					while (!ft_charset(str[i]))
						to_search[t++] = str[i++];
					to_search[t++] = '\0';//++ becuse we need it later
					dest = ftstrdup(to_search);
					while (current)
					{
						if (ft_strncmp(dest, current->data, ft_strlen(dest)) == 0)
						{
							while (current->data[t] != '\0')
								line[k++] = current->data[t++];
							break ;
						}
						current = current->next;
					}
					free (dest);
					dest = NULL;
			}
		}
		else 		
			line[k++] = str[i++];
	}
	line[k] = '\0';
	return (ftstrdup(line));
}

