/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 12:00:00 by vananiev          #+#    #+#             */
/*   Updated: 2026/06/11 15:00:00 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_weapon_switch_keys(t_game *game, mlx_key_data_t keydata,
	int pressed)
{
	if (keydata.key == MLX_KEY_1)
		game->input.n1 = pressed;
	if (keydata.key == MLX_KEY_2)
		game->input.n2 = pressed;
	if (keydata.key == MLX_KEY_3)
		game->input.n3 = pressed;
	if (keydata.key == MLX_KEY_4)
		game->input.n4 = pressed;
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
	{
		if (game->mouse_locked)
		{
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
			game->mouse_locked = 0;
		}
		else
		{
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
			game->mouse_locked = 1;
		}
	}
}

void	handle_action_flags(t_game *game, mlx_key_data_t keydata, int pressed)
{
	if (keydata.key == MLX_KEY_F)
		game->input.f = pressed;
	if (keydata.key == MLX_KEY_X)
		game->input.x = pressed;
}

#ifdef BONUS

void	handle_space_action(t_game *game, mlx_key_data_t keydata)
{
	if (keydata.key != MLX_KEY_SPACE || keydata.action != MLX_PRESS)
		return ;
	if (game->player->gun->current_weapon == HANDS)
	{
		if (!game->player->hands->anim->playing)
		{
			game->player->hands->mode = game->player->hands->next_punch;
			if (game->player->hands->next_punch == HAND_LEFT)
				game->player->hands->next_punch = HAND_RIGHT;
			else
				game->player->hands->next_punch = HAND_LEFT;
			game->player->hands->anim->playing = 1;
			game->player->hands->anim->current = 0;
			game->player->hands->anim->imgs[HAND_IDLE][0]
				->instances[0].enabled = false;
			attack(game, HANDS);
		}
	}
	else
		attack(game, SHOTGUN);
}

#else

void	handle_space_action(t_game *game, mlx_key_data_t keydata)
{
	(void)game;
	(void)keydata;
}

#endif
