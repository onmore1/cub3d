/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:24:42 by vananiev          #+#    #+#             */
/*   Updated: 2026/06/11 15:00:00 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifdef BONUS

static void	start_bonus(t_game *game)
{
	int	mini_map_tile_size;
	int	mini_map_size;

	mini_map_tile_size = WIDTH / 130;
	mini_map_size = MINIMAP_TILES * mini_map_tile_size;
	game->minimap = mlx_new_image(game->mlx, mini_map_size, mini_map_size);
	init_legs(game);
	init_hands(game);
	init_gun(game);
	init_doom_guy(game);
	mlx_image_to_window(game->mlx, game->minimap, WIDTH / 35, HEIGHT / 20);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
	draw_minimap_border(game, mini_map_tile_size);
	play_sound(&game->audio->song_1);
}

#else

static void	start_bonus(t_game *game)
{
	(void)game;
}

#endif

void	start(t_game *game)
{
	game->frame = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->frame)
		return ;
	mlx_image_to_window(game->mlx, game->frame, 0, 0);
	start_bonus(game);
	mlx_key_hook(game->mlx, key_hook, game);
	mlx_loop_hook(game->mlx, loop_hook, game);
	mlx_loop(game->mlx);
}

void	update_mouse(t_game *game)
{
	int		x;
	int		y;
	double	dx;
	double	dy;

	if (!game->mouse_locked)
		return ;
	mlx_get_mouse_pos(game->mlx, &x, &y);
	dx = x - WIDTH / 2;
	dy = y - HEIGHT / 2;
	if (dx != 0)
		rotate(game, dx * 0.002);
	if (dy != 0)
		game->player->pitch -= dy * 0.5;
	mlx_set_mouse_pos(game->mlx, WIDTH / 2, HEIGHT / 2);
}
