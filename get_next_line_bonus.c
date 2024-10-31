/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:33:07 by pleblond          #+#    #+#             */
/*   Updated: 2024/10/27 12:33:07 by pleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*readfile(char *buf, int fd)
{
	char	*buffer;
	int		i;

	i = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	while (!ft_strchr(buf, '\n') && i > 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			free(buf);
			free(buffer);
			return (NULL);
		}
		buffer[i] = '\0';
		buf = ft_strjoin(buf, buffer);
	}
	free(buffer);
	return (buf);
}

char	*update(char *line, char *buf)
{
	unsigned int	lenght_line;
	char			*newbuf;

	lenght_line = ft_strlen(line);
	newbuf = ft_substr(buf, lenght_line, ft_strlen(buf) - lenght_line);
	free(buf);
	buf = NULL;
	return (newbuf);
}

char	*get_next_line(int fd)
{
	char		*ligne;
	static char	*buffer[1024];
	size_t		len;

	len = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = readfile(buffer[fd], fd);
	if (!buffer[fd])
	{
		free(buffer[fd]);
		return (NULL);
	}
	while (buffer[fd][len] != '\0' && buffer[fd][len] != '\n')
		len++;
	ligne = ft_substr(buffer[fd], 0, len + 1);
	buffer[fd] = update(ligne, buffer[fd]);
	return (ligne);
}

// DEBUG //
/*
int main(void)
{
	char *line;
	int fd = open("tests/test.txt", O_RDONLY);

	if (fd < 1)
		return 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if(line)
		{
			printf("%s\n", line);
			free(line);
			line = get_next_line(fd);
		}
	}
	close(fd);
	return 0;
}
*/