int 	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

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

char    *replace_var(t_minishell *mini, char *str)//it must take quotes that open and close correctly
{
    t_env	*current;
	char	line[70000];//we check the str and we copy char by char in like, except it needs replace
	char	to_search[70000];
    int	i;
	int	k;
	int	t;
	char	*dest;
	int	len_to_move;

    current = mini->env;
    if (!current)
        return (NULL);
    i = 0;
	k = 0;
    while (str[i] != '\0')
    {
	 	if (str[i] == '\'')//when it founds ' , it conitinues copy exaclty until it founds the other ' .
		{

			line[k++] = str[i++];//copys openning '
			while (str[i] != '\'' && str[i] != '\0')
				line[k++] = str[i++];
			line[k++] = str[i++];//copys closing '
		}
		else if (str[i] == '$')//when finds $ , check the rules are needed to see if do replace
		{
			if (str[i + 1] == '\0' || str[i + 1]== '\"')//end of the sentence or finds $", copy
				line[k++] = str[i++];
			else if (str[i + 1] == 32)//space, copy
				line[k++] = str[i++];
		 	else if (str[i + 1] == '_')//$_
			{
				if (str[i + 2] == '\0' || str[i + 2] == 32 || str[i + 2] == '\"')//is after $_ is space or terminator or ", no copy $_
					i = i + 2;//skips $_
		 		//else if$_^@#&*
			}
		 	else if (ft_isalpha(str[i + 1]) || ft_isdigit(str[i + 1]) || str[i + 1] == '_')//while is letter, number, _ it has to change it if exist
			{
				i++;//we pass $
				t = 0;
			 	current = mini->env;
				len_to_move = 0;
				while (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_')
				{
					len_to_move++;
					to_search[t++] = str[i++];
				}
				to_search[t] = '\0';
				dest = ftstrdup(to_search);
				while (current)
				{
					if (ft_strncmp(dest, current->data, ft_strlen(dest)) == 0)
					{
						t = 0;
						while (current->data[t] != '\0')
						{
							while (len_to_move >= 0)
							{
								t++;
								len_to_move--;
								
							}
							line[k++] = current->data[t++];
						}
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
