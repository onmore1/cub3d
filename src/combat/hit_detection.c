/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_detection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 09:47:06 by cpinas            #+#    #+#             */
/*   Updated: 2026/05/27 12:00:00 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_weapon_damage(t_game *game, double ray_dist)
{
	t_weapon	current;

	current = game->player->gun->current_weapon;
	if (current == SHOTGUN)
	{
		if (ray_dist < 2.0)
			return (100);
		if (ray_dist < 4.0)
			return (50);
		return (25);
	}
	else if (current == M_GUN)
		return (15);
	else if (current == LEGS)
		return (0);
	else if (current == PISTOL)
		return (25);
	else if (current == HANDS)
		return (75);
	return (0);
}

static void	combo(t_game *game, int *killed, double *first_kill_time)
{
	double	current_time;

	current_time = mlx_get_time();
	if (*killed == 1)
		*first_kill_time = current_time;
	if (*killed >= 3 && (current_time - *first_kill_time) <= 5.0)
	{
		play_sound(&game->audio->announcer_1);
		*killed = 0;
		*first_kill_time = 0.0;
	}
	else if (*first_kill_time > 0.0 && (current_time - *first_kill_time) > 5.0)
	{
		*killed = 0;
		*first_kill_time = 0.0;
	}
}

static void	hit_enemy(t_game *game, int i, int damage)
{
	static int		killed = 0;
	static double	first_kill_time = 0.0;

	if (game->player->gun->current_weapon == HANDS)
		play_sound(&game->audio->hands_punch);
	game->enemies[i].hp -= damage;
	if (game->enemies[i].hp > 0)
	{
		game->enemies[i].hurt = 1;
		game->enemies[i].hurt_timer = 0;
		game->enemies[i].anim_frame = 45;
		return ;
	}
	killed++;
	game->map->left--;
	game->enemies[i].alive = 0;
	game->enemies[i].anim_frame = 45;
	game->enemies[i].anim_timer = 0;
	game->doom_guy->face = HAPPY;
	play_sound(&game->audio->kill_sound);
	game->doom_guy->last_time = mlx_get_time();
	combo(game, &killed, &first_kill_time);
}

static void	apply_kick(t_game *game, int i)
{
	double	new_x;
	double	new_y;

	new_x = game->enemies[i].x + game->player->dir_x;
	new_y = game->enemies[i].y + game->player->dir_y;
	if (new_y < 0 || new_y >= game->map->height)
		return ;
	if (new_x < 0 || new_x >= game->map->width)
		return ;
	if (game->map->grid[(int)new_y][(int)new_x] == '1')
		return ;
	game->enemies[i].target_x = new_x;
	game->enemies[i].target_y = new_y;
	game->enemies[i].knockback = 1;
	game->enemies[i].attacking = 0;
}

int	check_enemy_action(t_game *game, t_probe *p)
{
	int		i;
	double	threshold;

	if (p->weapon == LEGS)
		threshold = 0.5;
	else if (p->weapon == HANDS)
		threshold = 0.2;
	else
		threshold = 0.25;
	i = check_ray_hits_enemy(game, p->test_x, p->test_y, threshold);
	if (i == -1)
		return (0);
	if (p->weapon == LEGS || (p->weapon == HANDS && threshold == 0.5))
		apply_kick(game, i);
	if (p->weapon == HANDS || (p->weapon != LEGS && threshold == 0.25))
		hit_enemy(game, i, get_weapon_damage(game, p->ray_dist));
	return (1);
}
