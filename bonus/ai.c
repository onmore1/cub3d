/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 14:53:20 by vananiev          #+#    #+#             */
/*   Updated: 2026/05/29 13:16:58 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_walkable_tile(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map->width)
		return (0);
	if (y < 0 || y >= game->map->height)
		return (0);
	if (game->map->grid[y][x] == '1')
		return (0);
	if (game->map->grid[y][x] == '3')
		if (is_door_blocking(game, x, y))
			return (0);
	return (1);
}

int	already_occupied(t_game *game, int self_i, double x, double y)
{
	int		i;
	double	dx;
	double	dy;
	double	dist_sq;

	i = 0;
	while (i < game->enemy_count)
	{
		if (i != self_i && game->enemies[i].alive)
		{
			dx = game->enemies[i].x - x;
			dy = game->enemies[i].y - y;
			dist_sq = dx * dx + dy * dy;
			if (dist_sq < 0.10)
				return (1);
		}
		i++;
	}
	return (0);
}

void	reset_dist_field(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			game->dist_field[y][x] = -1;
			x++;
		}
		y++;
	}
}

static void	push_neighbor(t_game *game, int coords[4], int *queue, int *tail)
{
	int	nx;
	int	ny;

	nx = coords[NEIGHBOR_X];
	ny = coords[NEIGHBOR_Y];
	if (is_walkable_tile(game, nx, ny) && game->dist_field[ny][nx] == -1)
	{
		game->dist_field[ny][nx] = game->dist_field[coords[CURRENT_Y]]
		[coords[CURRENT_X]] + 1;
		queue[(*tail)++] = ny * game->map->width + nx;
	}
}

void	push_neighbors(t_game *game, int curr[2], int *queue, int *tail)
{
	static const int	dx[4] = {1, -1, 0, 0};
	static const int	dy[4] = {0, 0, 1, -1};
	int					coords[4];
	int					i;

	coords[CURRENT_X] = curr[POS_X];
	coords[CURRENT_Y] = curr[POS_Y];
	i = 0;
	while (i < 4)
	{
		coords[NEIGHBOR_X] = curr[POS_X] + dx[i];
		coords[NEIGHBOR_Y] = curr[POS_Y] + dy[i];
		push_neighbor(game, coords, queue, tail);
		i++;
	}
}
