/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_settings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:30:50 by vananiev          #+#    #+#             */
/*   Updated: 2026/06/17 17:48:31 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	count_settings(t_game *game, int counts[2])
{
	int	index;
	int	i;

	i = 0;
	while (i < 2)
		counts[i++] = 0;
	index = 0;
	while (game->map->lines[index])
	{
		if (check_if_surface(game->map->lines[index]) == FLOOR)
			counts[0]++;
		if (check_if_surface(game->map->lines[index]) == CEILING)
			counts[1]++;
		index++;
	}
}

int	check_duplicates(t_game *game)
{
	int	counts[2];

	count_settings(game, counts);
	if (counts[0] > 1)
		return (printf("Error: duplicate FLOOR color\n"), 1);
	if (counts[1] > 1)
		return (printf("Error: duplicate CEILING color\n"), 1);
	return (0);
}

int	check_all_settings_present(t_game *game, int mode)
{
	if (!game->walls[NORTH].path)
	{
		if (mode == 1)
			printf("Error: missing NORTH texture\n");
		return (1);
	}
	if (!game->walls[SOUTH].path)
	{
		if (mode == 1)
			printf("Error: missing SOUTH texture\n");
		return (1);
	}
	if (!game->walls[EAST].path)
	{
		if (mode == 1)
			printf("Error: missing EAST texture\n");
		return (1);
	}
	if (!game->walls[WEST].path)
	{
		if (mode == 1)
			printf("Error: missing WEST texture\n");
		return (1);
	}
	return (0);
}

static int	handle_line(char *line, t_game *game)
{
	int				direction;
	int				surface;
	static bool		map_started;

	if (check_if_map_start(line) == true)
		map_started = true;
	direction = check_if_cardinal_direction(line);
	if (direction != -1)
		return (extract_path(line, game, direction));
	surface = check_if_surface(line);
	if (surface != -1)
		return (extract_color(line, game->colors[surface]));
	if (check_if_surface(line) == -1 || check_if_cardinal_direction(line) == -1)
		if (!check_if_empty_line(line) && surface == -1 && direction == -1
			&& map_started == false)
			return (printf("Invalid line detected: %s", line), 1);
	return (0);
}

int	check_settings(t_game *game)
{
	int	index;

	index = 0;
	while (game->map->lines[index])
	{
		if (handle_line(game->map->lines[index], game))
			return (1);
		index++;
	}
	if (check_duplicates(game) || check_all_settings_present(game, 1))
		return (1);
	if (*game->colors[CEILING] == -1 || *game->colors[FLOOR] == -1)
		return (printf("Missing color fo Ceiling or Floor\n"), 1);
	return (0);
}
