/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:24:42 by vananiev          #+#    #+#             */
/*   Updated: 2026/06/11 15:00:00 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifdef BONUS

static void	loop_bonus_pre(t_game *game)
{
	update_mouse(game);
	update_doors(game);
	compute_dist_field(game);
	update_enemies(game);
	update_enemy_animations(game);
}

static void	loop_bonus_post(t_game *game)
{
	run_anim_gun(game);
	run_anim_legs(game);
	run_anim_hands(game);
	minimap(game);
	check_if_end(game);
	run_guy_anim(game);
	update_hp_display(game);
	if (game->input.space && game->player->gun->current_weapon != HANDS)
		attack(game, SHOTGUN);
}

#else

static void	loop_bonus_pre(t_game *game)
{
	(void)game;
}

static void	loop_bonus_post(t_game *game)
{
	(void)game;
}

#endif

void	loop_hook(void *param)
{
	t_game	*game;
	double	current_time;

	game = (t_game *)param;
	current_time = mlx_get_time();
	game->delta_time = current_time - game->last_time;
	game->last_time = current_time;
	loop_bonus_pre(game);
	update_player(game);
	render(game);
	loop_bonus_post(game);
}
