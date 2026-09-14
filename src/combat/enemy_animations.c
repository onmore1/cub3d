/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_animations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 18:06:24 by vananiev          #+#    #+#             */
/*   Updated: 2026/05/27 12:00:00 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	play_hurt_anim(double delta_time, t_enemy *enemy)
{
	enemy->hurt_timer += delta_time;
	if (enemy->hurt_timer >= 0.20)
	{
		enemy->hurt = 0;
		if (enemy->alive)
			enemy->anim_frame = 0;
		enemy->hurt_timer = 0;
	}
}

static void	play_death_anim(double delta_time, t_enemy *enemy)
{
	enemy->anim_timer += delta_time;
	if (enemy->anim_timer >= 0.15)
	{
		enemy->anim_timer = 0;
		if (enemy->anim_frame < 49)
			enemy->anim_frame++;
	}
}

static void	play_walk_anim(double delta_time, t_enemy *enemy)
{
	if (!enemy->alive || enemy->hurt_timer)
		return ;
	enemy->anim_timer += delta_time;
	if (enemy->anim_timer >= 0.20)
	{
		enemy->anim_timer = 0;
		if (enemy->anim_frame < 32)
			enemy->anim_frame += 8;
		else
			enemy->anim_frame = 0;
	}
}

static void	play_attack_anim(double delta_time, t_enemy *enemy)
{
	if (!enemy->alive || enemy->hurt_timer || enemy->moving)
	{
		enemy->attacking = 0;
		return ;
	}
	enemy->anim_timer += delta_time;
	if (enemy->anim_timer >= 0.12)
	{
		enemy->anim_timer = 0;
		if (enemy->anim_frame >= 43)
		{
			enemy->tried_to_attack = 1;
			enemy->anim_frame = 0;
			enemy->attacking = 0;
			enemy->close = 0;
			return ;
		}
		enemy->attacking = 1;
		if (enemy->anim_frame < 40)
			enemy->anim_frame = 40;
		else if (enemy->anim_frame >= 40)
			enemy->anim_frame++;
	}
}

void	update_enemy_animations(t_game *game)
{
	int		i;
	t_enemy	*enemy;
	double	delta_time;

	delta_time = game->delta_time;
	i = 0;
	while (i < game->enemy_count)
	{
		enemy = &game->enemies[i];
		if (enemy->hurt)
			play_hurt_anim(delta_time, enemy);
		if (!enemy->alive)
			play_death_anim(delta_time, enemy);
		if (enemy->moving)
			play_walk_anim(delta_time, enemy);
		if (enemy->close)
			play_attack_anim(delta_time, enemy);
		i++;
	}
}
