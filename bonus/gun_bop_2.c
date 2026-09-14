/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_bop_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 12:00:00 by vananiev          #+#    #+#             */
/*   Updated: 2026/05/29 13:22:07 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	apply_strafe_tilt(t_anim *gun, t_game *game)
{
	static double	strafe_tilt = 0.0;
	double			target_tilt;

	target_tilt = 0.0;
	if (game->input.a)
		target_tilt = -4.0;
	else if (game->input.d)
		target_tilt = 4.0;
	if (game->input.lshift && (game->input.a || game->input.d))
		target_tilt *= 1.5;
	lerp(target_tilt, &strafe_tilt, 0.2);
	gun->bob_x += strafe_tilt;
}

static void	move_gun(t_anim *gun, t_game *game, double *y_boost)
{
	double	target_boost;
	double	shift_mult;
	double	calculated_x;
	double	target_x;
	double	target_y;

	gun->bob_time += game->delta_time * 8.0;
	if (game->input.lshift)
		target_boost = 20.0;
	else
		target_boost = 8.0;
	lerp(target_boost, y_boost, 0.08);
	if (game->input.lshift)
		shift_mult = 25.0;
	else
		shift_mult = 20.0;
	calculated_x = sin(gun->bob_time) * shift_mult;
	if (game->input.a && calculated_x < 0)
		target_x = calculated_x * 1.2;
	else
		target_x = calculated_x;
	target_y = sin(gun->bob_time * 2) * (*y_boost);
	lerp(target_x, &gun->bob_x, 0.2);
	lerp(target_y, &gun->bob_y, 0.2);
}

static void	update_bob_values(t_game *game, t_anim *gun, int moving)
{
	static double	y_boost = 0.0;

	if (moving)
		move_gun(gun, game, &y_boost);
	else
	{
		lerp(0.0, &y_boost, 0.08);
		lerp(0.0, &gun->bob_x, 0.10);
		lerp(0.0, &gun->bob_y, 0.10);
	}
}

static void	setup_gun_state(t_game *game, t_anim **gun, int *idx, int *base_x)
{
	if (game->player->gun->current_weapon == HANDS)
	{
		*gun = game->player->hands->anim;
		*idx = game->player->hands->mode;
		if (*idx == HAND_RIGHT)
			*base_x = WIDTH / 2;
		else
			*base_x = WIDTH / 4;
		return ;
	}
	*gun = game->player->gun;
	*idx = (*gun)->current_weapon;
	if (*idx == M_GUN)
		*base_x = WIDTH / 2.4;
	else
		*base_x = WIDTH / 1.5 - (int)(*gun)->imgs[*idx][0]->width / 2;
}

void	update_gun_bob(t_game *game)
{
	t_anim	*gun;
	int		base[2];
	int		moving;
	int		i;
	int		idx;

	setup_gun_state(game, &gun, &idx, &base[0]);
	moving = game->input.w || game->input.s
		|| game->input.a || game->input.d;
	base[1] = HEIGHT - (int)gun->imgs[idx][0]->height;
	update_bob_values(game, gun, moving);
	apply_strafe_tilt(gun, game);
	apply_forward_lean(gun, game, 0);
	i = 0;
	while (i < gun->count[idx])
	{
		gun->imgs[idx][i]->instances[0].x = base[0] + (int)gun->bob_x;
		gun->imgs[idx][i]->instances[0].y = base[1] + (int)gun->bob_y;
		i++;
	}
}
