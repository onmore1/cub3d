/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 16:50:38 by vananiev          #+#    #+#             */
/*   Updated: 2026/06/11 15:00:00 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_game *game, double x, double y)
{
	if (x < 0 || y < 0 || y >= game->map->height || x >= game->map->width)
		return (1);
	if (game->map->grid[(int)y][(int)x] == '1')
		return (1);
	return (0);
}

static void	update_pitch(t_game *game)
{
	if (game->input.up)
		game->player->pitch -= 200 * game->delta_time;
	if (game->input.down)
		game->player->pitch += 200 * game->delta_time;
	if (game->player->pitch > HEIGHT / 2)
		game->player->pitch = HEIGHT / 2;
	if (game->player->pitch < -HEIGHT / 2)
		game->player->pitch = -HEIGHT / 2;
}

#ifdef BONUS

static void	update_player_bonus(t_game *game)
{
	if (game->input.f && !game->player->legs->playing)
		attack(game, LEGS);
}

#else

static void	update_player_bonus(t_game *game)
{
	(void)game;
}

#endif

void	update_player(t_game *game)
{
	game->player->speed = 2.5 * game->delta_time;
	if (game->input.lshift)
		game->player->speed *= 1.5;
	if (game->input.w)
		move_forward(game, game->player->speed);
	if (game->input.s)
		move_backward(game, game->player->speed);
	if (game->input.a)
		strafe_left(game, game->player->speed);
	if (game->input.d)
		strafe_right(game, game->player->speed);
	if (game->input.left)
		rotate_left(game);
	if (game->input.right)
		rotate_right(game);
	update_player_bonus(game);
	update_pitch(game);
}
