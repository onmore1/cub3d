/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_detection_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 12:00:00 by vananiev          #+#    #+#             */
/*   Updated: 2026/06/11 13:14:45 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	play_attack_sound(t_game *game)
{
	if (game->player->gun->current_weapon == M_GUN)
		play_sound(&game->audio->m_gun);
	else if (game->player->gun->current_weapon == SHOTGUN)
		play_sound(&game->audio->shotgun);
	else if (game->player->gun->current_weapon == HANDS)
		play_sound(&game->audio->hands_woosh);
	else if (game->player->gun->current_weapon == PISTOL)
		play_sound(&game->audio->pistol);
}

int	check_ray_hits_enemy(t_game *game, double x, double y, double threshold)
{
	int		i;
	double	dx;
	double	dy;
	double	dist_sq;

	i = 0;
	while (i < game->enemy_count)
	{
		if (!game->enemies[i].alive)
		{
			i++;
			continue ;
		}
		dx = game->enemies[i].x - x;
		dy = game->enemies[i].y - y;
		dist_sq = dx * dx + dy * dy;
		if (dist_sq < threshold)
			return (i);
		i++;
	}
	return (-1);
}

static void	shoot(t_probe *p, double hit_range, t_game *game)
{
	p->ray_dist = 0.0;
	while (p->ray_dist < hit_range)
	{
		p->test_x = game->player->pos_x + game->player->dir_x * p->ray_dist;
		p->test_y = game->player->pos_y + game->player->dir_y * p->ray_dist;
		if (game->map->grid[(int)p->test_y][(int)p->test_x] == '1')
			return ;
		else if (game->map->grid[(int)p->test_y][(int)p->test_x] == '3'
				&& is_door_blocking(game, p->test_x, p->test_y))
			return ;
		if (check_enemy_action(game, p))
			return ;
		p->ray_dist += 0.05;
	}
}

static int	prepare_attack(t_game *game, int weapon, double *hit_range)
{
	if (!game->player->gun->ammo[game->player->gun->current_weapon]
		&& weapon != HANDS && weapon != LEGS)
		return (0);
	if (weapon == HANDS || weapon == LEGS)
	{
		*hit_range = 1.0;
		if (weapon == HANDS)
			play_sound(&game->audio->hands_woosh);
		return (1);
	}
	if (game->player->gun->playing)
		return (0);
	*hit_range = 20.0;
	return (1);
}

void	attack(t_game *game, int weapon)
{
	t_probe	p;
	double	hit_range;

	p.weapon = weapon;
	if (!prepare_attack(game, weapon, &hit_range))
		return ;
	shoot(&p, hit_range, game);
}
