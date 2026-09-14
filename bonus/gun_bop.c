/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_bop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:12:10 by vananiev          #+#    #+#             */
/*   Updated: 2026/05/29 12:52:00 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	lerp(double target, double *to_increase, double rate)
{
	*to_increase += (target - *to_increase) * rate;
}

static void	apply_lean_walking(t_anim *gun, t_game *game, double *forward_lean)
{
	double	target_lean;

	target_lean = 0.0;
	if (game->input.w)
		target_lean = -3.0;
	else if (game->input.s)
		target_lean = 4.0;
	if (game->input.lshift && (game->input.w || game->input.s))
		target_lean *= 1.5;
	lerp(target_lean, forward_lean, 0.2);
	(void)gun;
}

static void	apply_lean_shooting(t_anim *gun, double *forward_lean)
{
	double	target_lean;

	target_lean = 0.0;
	if (gun->current_weapon == SHOTGUN)
		target_lean = 27;
	else if (gun->current_weapon == M_GUN)
		target_lean = 25;
	else if (gun->current_weapon == PISTOL)
		target_lean = -5;
	else if (gun->current_weapon == HANDS)
		return ;
	lerp(target_lean, forward_lean, 1);
}

static void	apply_lean_recoil(t_anim *gun, double *forward_lean)
{
	double	target_lean;

	target_lean = 0.0;
	if (gun->current_weapon == SHOTGUN)
	{
		if (target_lean <= 90)
			target_lean = 90;
	}
	else if (gun->current_weapon == M_GUN)
	{
		if (target_lean <= 30)
			target_lean = 30;
	}
	else if (gun->current_weapon == PISTOL)
	{
		if (target_lean <= 30)
			target_lean = 30;
	}
	else if (gun->current_weapon == HANDS)
		return ;
	lerp(target_lean, forward_lean, 5);
}

void	apply_forward_lean(t_anim *gun, t_game *game, int mode)
{
	static double	forward_lean = 0.0;

	if (mode == 0)
		apply_lean_walking(gun, game, &forward_lean);
	else if (mode == 1)
		apply_lean_shooting(gun, &forward_lean);
	else if (mode == 2)
		apply_lean_recoil(gun, &forward_lean);
	gun->bob_y += forward_lean;
	if (gun->bob_y > 500.0)
		gun->bob_y = 500.0;
	if (gun->bob_y < -600.0)
		gun->bob_y = 300.0;
}
