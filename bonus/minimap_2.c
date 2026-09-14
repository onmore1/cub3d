/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 12:00:00 by vananiev          #+#    #+#             */
/*   Updated: 2026/06/11 14:19:54 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap_border(t_game *game, int tile_size)
{
	mlx_image_t	*border;
	int			size;
	int			x;
	int			y;

	size = MINIMAP_TILES * tile_size;
	border = mlx_new_image(game->mlx, size, size);
	if (!border)
		return ;
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			if (x < 10 || x >= size - 10 || y < 10 || y >= size - 10)
				mlx_put_pixel(border, x, y, 0xFFFFFFFF);
			else
				mlx_put_pixel(border, x, y, 0x00000000);
			x++;
		}
		y++;
	}
	mlx_image_to_window(game->mlx, border, WIDTH / 35, HEIGHT / 20);
}

static int	is_enemy_tile(t_game *game, int map_x, int map_y)
{
	int	index;

	if (map_x < 0 || map_x >= game->map->width)
		return (0);
	if (map_y < 0 || map_y >= game->map->height)
		return (0);
	index = 0;
	while (index < game->enemy_count)
	{
		if (game->enemies[index].alive
			&& map_x == (int)game->enemies[index].x
			&& map_y == (int)game->enemies[index].y
			&& game->enemies[index].marked)
			return (1);
		else if (!game->enemies[index].alive
			&& map_x == (int)game->enemies[index].x
			&& map_y == (int)game->enemies[index].y
			&& game->enemies[index].marked)
			return (2);
		index++;
	}
	return (0);
}

static void	process_minimap_tile(t_game *game, int tile_x, int tile_y,
		int tile_size)
{
	int	coords[4];
	int	res;

	coords[0] = tile_x;
	coords[1] = tile_y;
	coords[2] = (int)game->player->pos_x - (MINIMAP_TILES / 2) + tile_x;
	coords[3] = (int)game->player->pos_y - (MINIMAP_TILES / 2) + tile_y;
	draw_tile(game, coords, tile_size);
	res = is_enemy_tile(game, coords[2], coords[3]);
	if (res == 1)
		draw_enemy(game, tile_x, tile_y, tile_size);
	else if (res == 2)
		draw_cross(game, tile_x, tile_y, tile_size);
}

static void	draw_map_tiles(t_game *game, int tile_size)
{
	int	tile_x;
	int	tile_y;

	tile_y = 0;
	while (tile_y < MINIMAP_TILES)
	{
		tile_x = 0;
		while (tile_x < MINIMAP_TILES)
		{
			process_minimap_tile(game, tile_x, tile_y, tile_size);
			tile_x++;
		}
		tile_y++;
	}
}

void	minimap(t_game *game)
{
	int	tile_size;

	tile_size = WIDTH / 130;
	draw_map_tiles(game, tile_size);
	draw_player(game, tile_size);
}
