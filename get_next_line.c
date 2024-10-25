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

static readfile(char *buf, int fd)
{
	char *buffer;
	int	i;

	i = 1;
	buffer = malloc(sizeof(char *) * (BUFFER_SIZE + 1));
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

char    *get_next_line(int fd)
{
	static char	*str = NULL;
}