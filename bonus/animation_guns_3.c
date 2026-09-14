/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_guns_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 12:00:00 by vananiev          #+#    #+#             */
/*   Updated: 2026/05/29 11:56:33 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_hands_anim(t_game *game, t_hands *hands)
{
	t_render_cfg	cfg;

	hands->anim->pathes[0] = load_hands();
	hands->anim->pathes[1] = load_punch_l();
	hands->anim->pathes[2] = load_punch_r();
	hands->anim->count[0] = 9;
	hands->anim->count[1] = 9;
	hands->anim->count[2] = 9;
	hands->anim->delay[0] = 100;
	hands->anim->delay[1] = 40;
	hands->anim->delay[2] = 40;
	cfg.x_ratio = 1.0 / 1.5;
	cfg.size = 300.0;
	pre_render_set(game, hands->anim, 0, cfg);
	cfg.size = 400.0;
	pre_render_set(game, hands->anim, 1, cfg);
	pre_render_set(game, hands->anim, 2, cfg);
}

void	init_hands(t_game *game)
{
	t_hands	*hands;

	game->player->hands = malloc(sizeof(t_hands));
	if (!game->player->hands)
		return (clean_up(game));
	hands = game->player->hands;
	hands->anim = malloc(sizeof(t_anim));
	if (!hands->anim)
		return (clean_up(game));
	setup_hands_anim(game, hands);
	hands->anim->current = 0;
	hands->anim->last_time = 0;
	hands->anim->playing = 0;
	hands->anim->bob_time = 0;
	hands->anim->bob_x = 0;
	hands->anim->bob_y = 0;
	hands->anim->current_weapon = 0;
	hands->mode = HAND_IDLE;
	hands->next_punch = HAND_LEFT;
	hands->just_switched = 0;
	hands->anim->imgs[0][0]->instances[0].enabled = false;
}
