/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 12:00:00 by vananiev          #+#    #+#             */
/*   Updated: 2026/05/28 14:29:13 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	update_single_enemy(t_game *game, int i, double move_dist)
{
	t_enemy	*enemy;

	enemy = &game->enemies[i];
	if (!enemy->alive)
		return (0);
	if (enemy->knockback)
		return (update_knockback(enemy, game, i));
	if (enemy->attacking)
	{
		enemy->moving = 0;
		return (0);
	}
	if (enemy->spotted && (mlx_get_time() - enemy->spot_time) < 5.0)
		return (handle_spotted_enemy(game, enemy, i, move_dist));
	enemy->moving = 0;
	return (0);
}

void	update_enemies(t_game *game)
{
	double	move_dist;
	int		i;

	move_dist = game->delta_time * ENEMY_SPEED;
	i = 0;
	while (i < game->enemy_count)
	{
		update_single_enemy(game, i, move_dist);
		i++;
	}
}
