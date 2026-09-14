/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_settings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:39:25 by vananiev          #+#    #+#             */
/*   Updated: 2026/06/12 14:19:31 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_textures(t_game *game)
{
	int	index;

	game->walls = malloc(sizeof(t_texture) * 4);
	if (!game->walls)
		return (1);
	index = 0;
	while (index < 4)
	{
		game->walls[index].path = NULL;
		game->walls[index].img = NULL;
		index++;
	}
	return (0);
}

int	init_colors(t_game *game)
{
	int	index;

	game->colors = malloc(sizeof(int *) * 2);
	if (!game->colors)
		return (1);
	index = 0;
	while (index < 2)
	{
		game->colors[index] = malloc(sizeof(int) * 3);
		if (!game->colors[index])
			return (1);
		game->colors[index][0] = -1;
		game->colors[index][1] = -1;
		game->colors[index][2] = -1;
		index++;
	}
	return (0);
}

int	check_player_spawn(t_game *game, int x, int y)
{
	if (ft_strchr("NSEW", game->map->grid[y][x]))
	{
		game->player->pos_x = x + 0.5;
		game->player->pos_y = y + 0.5;
		set_direction(game->player, game->map->grid[y][x]);
		game->map->grid[y][x] = '0';
		return (1);
	}
	return (0);
}
