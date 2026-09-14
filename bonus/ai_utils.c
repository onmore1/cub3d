/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 17:46:26 by vananiev          #+#    #+#             */
/*   Updated: 2026/05/28 14:29:20 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_enemy_to_target(t_enemy *enemy, double target[2],
		double move_dist)
{
	double	dx;
	double	dy;
	double	len;

	dx = target[POS_X] - enemy->x;
	dy = target[POS_Y] - enemy->y;
	len = sqrt(dx * dx + dy * dy);
	if (len > move_dist)
	{
		enemy->x += (dx / len) * move_dist;
		enemy->y += (dy / len) * move_dist;
	}
	else
	{
		enemy->x = target[POS_X];
		enemy->y = target[POS_Y];
	}
	enemy->moving = 1;
}

static void	handle_stuck_enemy(t_game *game, t_enemy *enemy)
{
	double	dx;
	double	dy;

	enemy->moving = 0;
	dx = game->player->pos_x - enemy->x;
	dy = game->player->pos_y - enemy->y;
	if (sqrt(dx * dx + dy * dy) < 0.9)
	{
		enemy->close = 1;
		if (enemy->tried_to_attack)
		{
			play_sound(&game->audio->getting_hurt);
			game->player->health -= 25;
			enemy->tried_to_attack = 0;
			game->doom_guy->face = HURT;
			game->doom_guy->last_time = mlx_get_time();
		}
	}
	else
		enemy->close = 0;
}

int	update_knockback(t_enemy *enemy, t_game *game, int self_i)
{
	double	next_x;
	double	next_y;

	next_x = enemy->x + (enemy->target_x - enemy->x) * 0.15;
	next_y = enemy->y + (enemy->target_y - enemy->y) * 0.15;
	if (already_occupied(game, self_i, next_x, next_y))
	{
		enemy->target_x = enemy->x;
		enemy->target_y = enemy->y;
		enemy->knockback = 0;
		enemy->moving = 0;
		return (1);
	}
	enemy->x = next_x;
	enemy->y = next_y;
	if (fabs(enemy->target_x - enemy->x) < 0.02
		&& fabs(enemy->target_y - enemy->y) < 0.02)
	{
		enemy->x = enemy->target_x;
		enemy->y = enemy->target_y;
		enemy->knockback = 0;
	}
	enemy->moving = 1;
	return (1);
}

int	handle_spotted_enemy(t_game *game, t_enemy *enemy,
		int i, double move_dist)
{
	int		next[2];
	double	target[2];

	if (!enemy_next_step(game, i, next))
	{
		handle_stuck_enemy(game, enemy);
		return (0);
	}
	enemy->tried_to_attack = 0;
	enemy->close = 0;
	target[POS_X] = next[POS_X] + 0.5;
	target[POS_Y] = next[POS_Y] + 0.5;
	move_enemy_to_target(enemy, target, move_dist);
	return (1);
}
