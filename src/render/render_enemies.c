/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_enemies.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 14:43:51 by cpinas            #+#    #+#             */
/*   Updated: 2026/05/27 12:00:00 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	sort_enemies(t_game *game)
{
	int		i;
	t_enemy	temp;

	i = 0;
	while (i < game->enemy_count - 1)
	{
		if (game->enemies[i].dist < game->enemies[i + 1].dist)
		{
			temp = game->enemies[i];
			game->enemies[i] = game->enemies[i + 1];
			game->enemies[i + 1] = temp;
			i = 0;
			continue ;
		}
		i++;
	}
}

static void	calc_enemy_distances(t_game *game)
{
	int		i;
	double	dx;
	double	dy;

	i = 0;
	while (i < game->enemy_count)
	{
		dx = game->player->pos_x - game->enemies[i].x;
		dy = game->player->pos_y - game->enemies[i].y;
		game->enemies[i].dist = dx * dx + dy * dy;
		i++;
	}
}

static void	init_enemy_transform(t_enemy_render *r, t_game *game, int i)
{
	r->sprite_x = game->enemies[i].x - game->player->pos_x;
	r->sprite_y = game->enemies[i].y - game->player->pos_y;
	r->inv_det = 1.0 / (game->player->plane_x * game->player->dir_y
			- game->player->dir_x * game->player->plane_y);
	r->transform_x = r->inv_det * (game->player->dir_y * r->sprite_x
			- game->player->dir_x * r->sprite_y);
	r->transform_y = r->inv_det * (-game->player->plane_y * r->sprite_x
			+ game->player->plane_x * r->sprite_y);
}

static int	should_skip_enemy(t_enemy_render *r, int screen_x)
{
	if (r->transform_y <= 0.01)
		return (1);
	if (screen_x < 0 || screen_x >= WIDTH)
		return (1);
	return (0);
}

void	render_enemies(t_game *game)
{
	int				i;
	t_enemy_render	r;
	int				screen_x;

	calc_enemy_distances(game);
	sort_enemies(game);
	i = 0;
	while (i < game->enemy_count)
	{
		init_enemy_transform(&r, game, i);
		screen_x = (int)((WIDTH / 2) * (1 + r.transform_x / r.transform_y));
		if (!should_skip_enemy(&r, screen_x)
			&& r.transform_y < game->z_buffer[screen_x])
			draw_enemy_sprite(game, &game->enemies[i], &r, screen_x);
		i++;
	}
}
