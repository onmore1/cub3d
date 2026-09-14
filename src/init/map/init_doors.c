/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:27:00 by leggo             #+#    #+#             */
/*   Updated: 2026/05/29 13:20:13 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_doors(t_game *game)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			if (game->map->grid[y][x] == '3')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static void	init_single_door(t_game *game, int x, int y, int idx)
{
	game->doors[idx].x = x;
	game->doors[idx].y = y;
	game->doors[idx].orientation = 0;
	game->doors[idx].open_amount = 0.0;
	game->doors[idx].speed = 2.2;
	game->doors[idx].is_opening = 0;
	game->doors[idx].is_closing = 0;
}

static void	populate_doors(t_game *game)
{
	int	y;
	int	x;
	int	idx;

	idx = 0;
	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			if (game->map->grid[y][x] == '3')
			{
				init_single_door(game, x, y, idx);
				idx++;
			}
			x++;
		}
		y++;
	}
}

int	init_doors(t_game *game)
{
	int	count;

	count = count_doors(game);
	game->door_count = count;
	if (count == 0)
		return (0);
	game->doors = malloc(sizeof(t_door) * count);
	if (!game->doors)
		return (1);
	populate_doors(game);
	return (0);
}
