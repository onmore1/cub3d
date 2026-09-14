/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:40:55 by vananiev          #+#    #+#             */
/*   Updated: 2025/09/08 13:44:26 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*leftover;

	buffer = NULL;
	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(leftover), leftover = NULL, NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(leftover), leftover = NULL, NULL);
	leftover = read_from_file(buffer, leftover, fd);
	free(buffer);
	if (!leftover)
		return (NULL);
	line = extract_line(leftover);
	if (!line)
		return (free(leftover), leftover = NULL, NULL);
	leftover = extract_leftover(leftover);
	return (line);
}

char	*read_from_file(char *buffer, char *leftover, int fd)
{
	ssize_t	bytes_read;

	bytes_read = 1;
	if (!leftover)
	{
		leftover = malloc(1);
		if (!leftover)
			return (NULL);
		leftover[0] = '\0';
	}
	while (bytes_read > 0 && !ft_strchr(leftover, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(leftover), NULL);
		buffer[bytes_read] = '\0';
		leftover = ft_strjoin_free(leftover, buffer);
		if (!leftover)
			return (NULL);
	}
	if (bytes_read == 0 && (!leftover || leftover[0] == '\0'))
		return (free(leftover), NULL);
	return (leftover);
}

char	*extract_line(char *leftover)
{
	int		to_allocate;
	int		index;
	char	*pure_line;

	to_allocate = 0;
	index = 0;
	if (!leftover)
		return (NULL);
	while (leftover[to_allocate] && leftover[to_allocate] != '\n')
		to_allocate++;
	if (leftover[to_allocate] == '\n')
		to_allocate++;
	pure_line = malloc(sizeof(char) * (to_allocate + 1));
	if (!pure_line)
		return (NULL);
	while (index < to_allocate)
	{
		pure_line[index] = leftover[index];
		index++;
	}
	pure_line[index] = '\0';
	return (pure_line);
}

char	*extract_leftover(char *buffer)
{
	int		start;
	char	*leftover;

	start = 0;
	if (!buffer)
		return (NULL);
	while (buffer[start] && buffer[start] != '\n')
		start++;
	if (buffer[start] == '\n')
		start++;
	if (buffer[start] == '\0')
		return (free(buffer), NULL);
	leftover = ft_strdup(buffer + start);
	free(buffer);
	return (leftover);
}
