/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 12:49:48 by vananiev          #+#    #+#             */
/*   Updated: 2026/06/11 15:00:00 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_movement_keys(t_game *game, mlx_key_data_t keydata,
		int pressed)
{
	step_sound(keydata, game);
	if (keydata.key == MLX_KEY_W)
		game->input.w = pressed;
	if (keydata.key == MLX_KEY_S)
		game->input.s = pressed;
	if (keydata.key == MLX_KEY_A)
		game->input.a = pressed;
	if (keydata.key == MLX_KEY_D)
		game->input.d = pressed;
	if (keydata.key == MLX_KEY_LEFT)
		game->input.left = pressed;
	if (keydata.key == MLX_KEY_RIGHT)
		game->input.right = pressed;
	if (keydata.key == MLX_KEY_LEFT_SHIFT)
		game->input.lshift = pressed;
	if (keydata.key == MLX_KEY_SPACE)
		game->input.space = pressed;
	if (keydata.key == MLX_KEY_UP)
		game->input.up = pressed;
	if (keydata.key == MLX_KEY_DOWN)
		game->input.down = pressed;
	if (keydata.key == MLX_MOUSE_BUTTON_LEFT)
		game->input.lbm = pressed;
	handle_action_flags(game, keydata, pressed);
	handle_weapon_switch_keys(game, keydata, pressed);
}

#ifdef BONUS

static void	key_hook_bonus(t_game *game, mlx_key_data_t keydata)
{
	if ((keydata.key == MLX_KEY_1 || keydata.key == MLX_KEY_2
			|| keydata.key == MLX_KEY_3 || keydata.key == MLX_KEY_4)
		&& keydata.action == MLX_PRESS)
		if (game->player->hands->mode == HAND_IDLE)
			switch_weapon(game);
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
		interact_with_doors(game);
	handle_space_action(game, keydata);
}

#else

static void	key_hook_bonus(t_game *game, mlx_key_data_t keydata)
{
	(void)game;
	(void)keydata;
}

#endif

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	int		pressed;

	game = param;
	pressed = (keydata.action != MLX_RELEASE);
	handle_movement_keys(game, keydata, pressed);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	key_hook_bonus(game, keydata);
}
