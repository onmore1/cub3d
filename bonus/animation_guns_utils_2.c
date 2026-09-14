/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_guns_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 12:00:00 by vananiev          #+#    #+#             */
/*   Updated: 2026/05/28 14:53:46 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**load_punch_l(void)
{
	static char	*pathes[] = {
		"assets/mellee/hands/PONGJ0.png",
		"assets/mellee/hands/PONGI0.png",
		"assets/mellee/hands/PONGH0.png",
		"assets/mellee/hands/PONGG0.png",
		"assets/mellee/hands/PONGF0.png",
		"assets/mellee/hands/PONGE0.png",
		"assets/mellee/hands/PONGD0.png",
		"assets/mellee/hands/PONGC0.png",
		"assets/mellee/hands/PONGB0.png",
		NULL
	};

	return (pathes);
}

char	**load_punch_r(void)
{
	static char	*pathes[] = {
		"assets/mellee/hands/PONGJ0 (1).png",
		"assets/mellee/hands/PONGI0 (1).png",
		"assets/mellee/hands/PONGH0 (1).png",
		"assets/mellee/hands/PONGG0 (1).png",
		"assets/mellee/hands/PONGF0 (1).png",
		"assets/mellee/hands/PONGE0 (1).png",
		"assets/mellee/hands/PONGD0 (1).png",
		"assets/mellee/hands/PONGC0 (1).png",
		"assets/mellee/hands/PONGB0 (1).png",
		NULL
	};

	return (pathes);
}

static void	deactivate_current_weapon(t_anim *gun, t_hands *hands)
{
	if (gun->current_weapon == HANDS)
		hands->anim->imgs[0][hands->anim->current]
			->instances[0].enabled = false;
	else
		gun->imgs[gun->current_weapon][gun->current]
			->instances[0].enabled = false;
	gun->current = 0;
	gun->playing = 0;
}

static void	apply_weapon_selection(t_game *game, t_anim *gun)
{
	if (game->input.n1)
		gun->current_weapon = M_GUN;
	else if (game->input.n2)
		gun->current_weapon = SHOTGUN;
	else if (game->input.n3)
		gun->current_weapon = PISTOL;
	else if (game->input.n4)
	{
		play_sound(&game->audio->hands_cracking);
		gun->current_weapon = HANDS;
	}
	apply_forward_lean(gun, game, 2);
}

void	switch_weapon(t_game *game)
{
	t_anim	*gun;
	t_hands	*hands;

	gun = game->player->gun;
	hands = game->player->hands;
	deactivate_current_weapon(gun, hands);
	if (!game->input.n4)
		play_sound(&game->audio->equip);
	apply_weapon_selection(game, gun);
	if (gun->current_weapon == HANDS)
	{
		hands->just_switched = 1;
		hands->mode = HAND_IDLE;
		hands->anim->current = 0;
		hands->anim->playing = 1;
		hands->anim->imgs[HAND_IDLE][0]->instances[0].enabled = true;
	}
	else
	{
		hands->anim->imgs[HAND_IDLE][0]->instances[0].enabled = false;
		hands->anim->playing = 0;
		gun->imgs[gun->current_weapon][0]->instances[0].enabled = true;
	}
}
