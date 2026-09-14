/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 12:30:00 by vananiev          #+#    #+#             */
/*   Updated: 2026/06/11 15:00:00 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifdef BONUS

void	step_sound(mlx_key_data_t keydata, t_game *game)
{
	static double	last_upt = 0.0;
	double			current_time;

	if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_D
		|| keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_S)
	{
		if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		{
			current_time = mlx_get_time();
			if (current_time - last_upt >= 0.4)
			{
				play_sound(&game->audio->step);
				last_upt = current_time;
			}
		}
	}
}

#else

void	step_sound(mlx_key_data_t keydata, t_game *game)
{
	(void)keydata;
	(void)game;
}

#endif

void	try_move(t_game *game, double dx, double dy, double speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player->pos_x + dx * speed;
	new_y = game->player->pos_y + dy * speed;
	if (!is_wall(game, new_x + PLAYER_RADIUS, game->player->pos_y)
		&& !is_wall(game, new_x - PLAYER_RADIUS, game->player->pos_y)
		&& !is_door_blocking(game, new_x, game->player->pos_y))
		game->player->pos_x = new_x;
	if (!is_wall(game, game->player->pos_x, new_y + PLAYER_RADIUS)
		&& !is_wall(game, game->player->pos_x, new_y - PLAYER_RADIUS)
		&& !is_door_blocking(game, game->player->pos_x, new_y))
		game->player->pos_y = new_y;
}

void	strafe_left(t_game *game, double speed)
{
	try_move(game, -game->player->plane_x, -game->player->plane_y, speed);
}

void	strafe_right(t_game *game, double speed)
{
	try_move(game, game->player->plane_x, game->player->plane_y, speed);
}
