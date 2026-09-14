/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 16:50:29 by vananiev          #+#    #+#             */
/*   Updated: 2026/06/11 14:16:45 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t	get_tile_color(t_game *game, int map_x, int map_y)
{
	if (map_x < 0 || map_x >= game->map->width)
		return (0x333333FF);
	if (map_y < 0 || map_y >= game->map->height)
		return (0x333333FF);
	if (game->map->grid[map_y][map_x] == '1')
		return (0x888888FF);
	return (0x222222FF);
}

void	draw_cross(t_game *game, int tile_x, int tile_y, int tile_size)
{
	int	margin;
	int	start_x;
	int	start_y;
	int	span;
	int	i;

	margin = tile_size / 4;
	start_x = tile_x * tile_size + margin;
	start_y = tile_y * tile_size + margin;
	span = tile_size - 2 * margin;
	i = 0;
	while (i < span)
	{
		mlx_put_pixel(game->minimap, start_x + i,
			start_y + i, 0xFF0000FF);
		mlx_put_pixel(game->minimap, start_x + i,
			start_y + span - 1 - i, 0xFF0000FF);
		i++;
	}
}

void	draw_player(t_game *game, int tile_size)
{
	int	center;
	int	size;
	int	pixel_x;
	int	pixel_y;

	center = (MINIMAP_TILES * tile_size) / 2;
	size = 7;
	pixel_y = center - size;
	while (pixel_y <= center + size)
	{
		pixel_x = center - size;
		while (pixel_x <= center + size)
		{
			mlx_put_pixel(game->minimap, pixel_x, pixel_y, 0x1D9E75FF);
			pixel_x++;
		}
		pixel_y++;
	}
}

void	draw_enemy(t_game *game, int tile_x, int tile_y, int tile_size)
{
	int	margin;
	int	pixel_x;
	int	pixel_y;
	int	end_x;
	int	end_y;

	margin = tile_size / 4;
	pixel_y = tile_y * tile_size + margin;
	end_y = (tile_y + 1) * tile_size - margin;
	end_x = (tile_x + 1) * tile_size - margin;
	while (pixel_y < end_y)
	{
		pixel_x = tile_x * tile_size + margin;
		while (pixel_x < end_x)
		{
			mlx_put_pixel(game->minimap, pixel_x, pixel_y, 0xFF0000FF);
			pixel_x++;
		}
		pixel_y++;
	}
}

void	draw_tile(t_game *game, int coords[4], int tile_size)
{
	uint32_t	color;
	int			pixel_x;
	int			pixel_y;
	int			end_x;
	int			end_y;

	color = get_tile_color(game, coords[2], coords[3]);
	pixel_y = coords[1] * tile_size;
	end_y = pixel_y + tile_size;
	while (pixel_y < end_y)
	{
		pixel_x = coords[0] * tile_size;
		end_x = pixel_x + tile_size;
		while (pixel_x < end_x)
		{
			mlx_put_pixel(game->minimap, pixel_x, pixel_y, color);
			pixel_x++;
		}
		pixel_y++;
	}
}
