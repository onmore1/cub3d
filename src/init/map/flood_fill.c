/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 17:47:04 by cpinas            #+#    #+#             */
/*   Updated: 2026/06/17 16:45:39 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	**allocate_visited(int height, int width)
{
	int	**array;
	int	i;

	array = (int **)malloc(height * sizeof(int *));
	if (!array)
		return (NULL);
	i = 0;
	while (i < height)
	{
		array[i] = (int *)malloc(width * sizeof(int));
		if (!array[i])
		{
			while (i >= 0)
				free(array[i--]);
			free(array);
			return (NULL);
		}
		ft_bzero((void *)array[i], width * sizeof(int));
		i++;
	}
	return (array);
}

void	free_visited(int **visited, int height)
{
	int	i;

	if (!visited)
		return ;
	i = 0;
	while (i < height)
	{
		if (visited[i])
			free(visited[i]);
		i++;
	}
	free(visited);
}

int	flood_fill(t_map *map, int **visited, int row, int col)
{
	if (row < 0 || row >= map->height
		|| col < 0 || col >= map->width)
		return (printf("Error: map is not enclosed by walls\n"), -1);
	if (visited[row][col]
		|| map->grid[row][col] == '1')
		return (0);
	if (visited[row][col] || map->grid[row][col] == '1')
		return (0);
	visited[row][col] = 1;
	if (flood_fill(map, visited, row - 1, col) == -1)
		return (-1);
	if (flood_fill(map, visited, row + 1, col) == -1)
		return (-1);
	if (flood_fill(map, visited, row, col - 1) == -1)
		return (-1);
	if (flood_fill(map, visited, row, col + 1) == -1)
		return (-1);
	return (0);
}

static int	check_unreachable(t_map *map, int **visited)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] == '0' && visited[i][j] == 0)
				return (printf("Error: map has unreachable areas\n"), 1);
			j++;
		}
		i++;
	}
	return (0);
}

int	validate_map_enclosed(t_map *map)
{
	int	**visited;
	int	player_row;
	int	player_col;

	visited = allocate_visited(map->height, map->width);
	if (!visited)
		return (1);
	player_row = map->p_pos / map->width;
	player_col = map->p_pos % map->width;
	if (flood_fill(map, visited, player_row, player_col) == -1)
		return (free_visited(visited, map->height), 1);
	if (check_unreachable(map, visited))
		return (free_visited(visited, map->height), 1);
	free_visited(visited, map->height);
	return (0);
}
