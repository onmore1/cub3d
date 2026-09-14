/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_guns.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 16:50:38 by vananiev          #+#    #+#             */
/*   Updated: 2026/05/28 13:09:47 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	tick_anim(t_anim *anim, int set, double now)
{
	int	prev;

	if ((now - anim->last_time) * 1000 < anim->delay[set])
		return ;
	prev = anim->current;
	anim->current++;
	anim->imgs[set][prev]->instances[0].enabled = false;
	if (anim->current >= anim->count[set])
	{
		anim->current = 0;
		anim->playing = 0;
	}
	anim->imgs[set][anim->current]->instances[0].enabled = true;
	anim->last_time = now;
}

static void	handle_gun_fire(t_game *game, t_anim *anim, int *stopper)
{
	if (anim->current != 1)
	{
		*stopper = 0;
		return ;
	}
	apply_forward_lean(game->player->gun, game, 1);
	play_attack_sound(game);
	if (*stopper)
		return ;
	game->player->gun->ammo[game->player->gun->current_weapon]--;
	*stopper = 1;
}

void	run_anim_gun(t_game *game)
{
	t_anim		*anim;
	static int	stopper;

	anim = game->player->gun;
	if (anim->current_weapon == HANDS)
		return ;
	update_gun_bob(game);
	if (game->input.space && !anim->playing)
	{
		if (game->player->gun->ammo[game->player->gun->current_weapon] > 0)
			anim->playing = 1;
	}
	if (!anim->playing)
		return ;
	handle_gun_fire(game, anim, &stopper);
	tick_anim(anim, anim->current_weapon, mlx_get_time());
}

void	run_anim_hands(t_game *game)
{
	t_hands	*hands;

	if (game->player->gun->current_weapon != HANDS)
		return ;
	hands = game->player->hands;
	update_gun_bob(game);
	if (!hands->anim->playing)
		return ;
	tick_anim(hands->anim, hands->mode, mlx_get_time());
	if (!hands->anim->playing && hands->mode != HAND_IDLE)
	{
		hands->anim->imgs[HAND_LEFT][0]->instances[0].enabled = false;
		hands->anim->imgs[HAND_RIGHT][0]->instances[0].enabled = false;
		hands->anim->imgs[HAND_IDLE][0]->instances[0].enabled = true;
		hands->just_switched = 0;
		hands->mode = HAND_IDLE;
	}
}

void	run_anim_legs(t_game *game)
{
	t_anim	*legs;
	int		punch;

	legs = game->player->legs;
	punch = game->input.f;
	if (punch)
		legs->playing = 1;
	if (!legs->playing)
		return ;
	tick_anim(legs, 0, mlx_get_time());
	if (legs->current == 0)
	{
		legs->imgs[0][legs->current]->instances[0].enabled = false;
		legs->playing = 0;
	}
	else
		legs->playing = 1;
}
