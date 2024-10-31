/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 23:14:01 by pleblond          #+#    #+#             */
/*   Updated: 2024/10/24 23:14:01 by pleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*readfile(int fd, char *buf)
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
	static char	*buffer = NULL;
	size_t		len;

	len = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = readfile(fd, buffer);
	if (!buffer)
		return (NULL);
	while (buffer[len] != '\0' && buffer[len] != '\n')
		len++;
	ligne = ft_substr(buffer, 0, len + 1);
	buffer = update(ligne, buffer);
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