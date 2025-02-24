/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:48:48 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/13 20:32:56 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "minishell.h"
#include <stdio.h>

char	*ft_line_save(char *line_save, int fd)
{
	char	*buffer;
	int		bytes_read;

	bytes_read = 1;
	buffer = (char *)ft_calloc_gnl(BUFFER_SIZE + 1, 1);
	if (!buffer)
		return (NULL);
	while (!ft_strchr((const char *)line_save, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), free(line_save), NULL);
		if (!line_save[0] && bytes_read == 0)
			return (free(buffer), free(line_save), printf("\nexit\n"),
				exit(1), NULL);
		else if (line_save[0] && bytes_read == 0)
			continue ;
		buffer[bytes_read] = '\0';
		line_save = ft_strjoin_gnl(line_save, buffer);
	}
	free(buffer);
	return (line_save);
}

char	*line_to_print(const char *line_save)
{
	size_t	len;
	size_t	i;
	char	*line;

	i = -1;
	len = ft_strclen(line_save, '\n') + 1;
	line = (char *)ft_calloc_gnl(len + 1, 1);
	if (!line)
		return (NULL);
	while (++i < len && line_save[i])
		line[i] = line_save[i];
	return (line);
}

char	*newline_save(char *line_save, int len_line)
{
	int		i;
	int		newline_len;
	char	*newline_saved;

	i = 0;
	if (!line_save[0])
		return (NULL);
	while (line_save[len_line] && line_save[len_line] != '\n')
		len_line++;
	if (line_save[len_line] == '\n')
		len_line++;
	newline_len = (ft_strclen(line_save, '\0') - len_line) + 1;
	newline_saved = (char *)ft_calloc_gnl(newline_len, 1);
	if (!newline_saved)
		return (NULL);
	while (line_save[i + len_line])
	{
		newline_saved[i] = line_save[i + len_line];
		i++;
	}
	newline_saved[i] = '\0';
	free(line_save);
	return (newline_saved);
}

char	*get_next_line(int fd)
{
	static char	*line_save[1024];
	char		*line;

	line = NULL;
	if (fd < 0 || fd >= 1024 || BUFFER_SIZE < 1)
		return (NULL);
	if (!line_save[fd])
		line_save[fd] = (char *)ft_calloc_gnl(1, 1);
	line_save[fd] = ft_line_save(line_save[fd], fd);
	if (!line_save[fd])
		return (NULL);
	line = line_to_print(line_save[fd]);
	if (!line)
		return (NULL);
	line_save[fd] = newline_save(line_save[fd], 0);
	if (!line_save[fd][0])
	{
		free(line_save[fd]);
		line_save[fd] = NULL;
	}
	return (line);
}

/* #include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	// line = get_next_line(fd);
	// printf("%s", line);
	// free(line);
	// line = get_next_line(fd);
	// printf("%s", line);
	// free(line);
	// line = get_next_line(fd);
	// printf("%s", line);
	// free(line);
	// line = get_next_line(fd);
	// printf("%s", line);
	// free(line);
	// line = get_next_line(fd);
	// printf("%s", line);
	// free(line);
	return (0);
} */