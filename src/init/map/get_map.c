/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 12:51:12 by vananiev          #+#    #+#             */
/*   Updated: 2026/05/25 14:13:51 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_map_height(char **lines, int start, t_map *map)
{
	int	h;

	h = 0;
	while (lines[start + h])
	{
		if (is_map_line(lines[start + h], 1, map))
			h++;
		else
			return (-1);
	}
	return (h);
}

int	get_max_width(t_map *map)
{
	int	i;
	int	max;
	int	len;

	i = 0;
	max = 0;
	while (i < map->height)
	{
		len = ft_strlen(map->grid[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

int	build_grid(t_map *map, int start)
{
	int	i;
	int	height;

	height = get_map_height(map->lines, start, map);
	if (height == -1)
		return (1);
	map->height = height;
	map->grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
		return (1);
	i = 0;
	while (i < map->height)
	{
		map->grid[i] = ft_strtrim(map->lines[start + i], "\n");
		if (!map->grid[i])
			return (1);
		i++;
	}
	map->grid[i] = NULL;
	return (0);
}

static char	**get_lines_helper(char *filename, int count)
{
	int		fd;
	int		index;
	char	*line;
	char	**lines;

	index = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	lines = malloc(sizeof(char *) * (count + 1));
	if (!lines)
		return (close(fd), NULL);
	line = get_next_line(fd);
	while (line != NULL)
	{
		lines[index] = ft_strdup(line);
		free(line);
		index++;
		line = get_next_line(fd);
	}
	lines[count] = NULL;
	close(fd);
	return (lines);
}

char	**get_lines(char *filename)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf("Error opening file: %s. %s\n",
				filename, strerror(errno)), NULL);
	line = get_next_line(fd);
	while (line != NULL)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (get_lines_helper(filename, count));
}
