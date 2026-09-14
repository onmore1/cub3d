/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:22:35 by vananiev          #+#    #+#             */
/*   Updated: 2026/06/12 13:15:55 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_player_found(t_map *map, int i, int j, int *found)
{
	if (ft_strchr("NSEW", map->grid[i][j]))
	{
		if (*found)
			return (printf("Error: multiple player start positions\n"), -1);
		*found = 1;
		map->player_dir = map->grid[i][j];
		map->p_pos = i * map->width + j;
	}
	return (0);
}

int	find_player_start(t_map *map)
{
	int	i;
	int	j;
	int	found;

	found = 0;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (check_player_found(map, i, j, &found) == -1)
				return (-1);
			j++;
		}
		i++;
	}
	if (!found)
		return (printf("Error: no player start position found\n"), -1);
	return (0);
}

static void	fill_line(char *new_line, char *old_line, int width)
{
	int	j;

	j = 0;
	while (j < width)
	{
		if (j < (int)ft_strlen(old_line))
			new_line[j] = old_line[j];
		else
			new_line[j] = ' ';
		j++;
	}
	new_line[j] = '\0';
}

int	normalize_grid(t_map *map)
{
	int		i;
	char	*new_line;

	map->width = get_max_width(map);
	i = 0;
	while (i < map->height)
	{
		new_line = malloc(map->width + 1);
		if (!new_line)
			return (1);
		fill_line(new_line, map->grid[i], map->width);
		free(map->grid[i]);
		map->grid[i] = new_line;
		i++;
	}
	return (0);
}

int	find_map_start(t_map *map)
{
	int	i;

	i = 0;
	while (map->lines[i] && !is_map_line(map->lines[i], 0, map))
		i++;
	if (!map->lines[i])
		return (printf("Error: no map found\n"), -1);
	return (i);
}
