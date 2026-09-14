/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_enemies_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 12:00:00 by vananiev          #+#    #+#             */
/*   Updated: 2026/05/28 10:42:23 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_enemy_pixel(t_game *game, int x, int y, uint32_t color)
{
	uint32_t	*frame;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	frame = (uint32_t *)game->frame->pixels;
	frame[y * WIDTH + x] = color;
}

static void	draw_sprite_column(t_sprite_draw *d)
{
	int			y;
	int			world_y;
	int			tex_y;
	uint32_t	color;

	y = 0;
	while (y < d->size)
	{
		world_y = d->start_y + y;
		if (world_y >= 0 && world_y < HEIGHT)
		{
			tex_y = d->frame_y * d->sprite_h
				+ (y * d->sprite_h) / d->size;
			color = ((uint32_t *)d->game->enemy_tex->pixels)
			[tex_y * d->game->enemy_tex->width + d->tex_x];
			if ((color >> 24) != 0)
				draw_enemy_pixel(d->game, d->world_x, world_y, color);
		}
		y++;
	}
}

static void	init_sprite_draw(t_sprite_draw *d, t_game *game,
	t_enemy *enemy, int screen_x)
{
	d->game = game;
	d->sprite_w = game->enemy_tex->width / SPRITE_COLS;
	d->sprite_h = game->enemy_tex->height / SPRITE_ROWS;
	d->frame = enemy->anim_frame;
	d->frame_x = d->frame % SPRITE_COLS;
	d->frame_y = d->frame / SPRITE_COLS;
	d->start_x = screen_x - d->size / 2;
	d->start_y = HEIGHT / 2 - d->size / 2 + game->player->pitch;
}

void	draw_enemy_sprite(t_game *game, t_enemy *enemy,
	t_enemy_render *r, int screen_x)
{
	t_sprite_draw	d;
	int				x;
	int				size;

	size = abs((int)(HEIGHT / r->transform_y));
	if (size > HEIGHT * 2)
		size = HEIGHT * 2;
	d.size = size;
	init_sprite_draw(&d, game, enemy, screen_x);
	x = 0;
	while (x < size)
	{
		d.world_x = d.start_x + x;
		if (d.world_x >= 0 && d.world_x < WIDTH
			&& r->transform_y <= game->z_buffer[d.world_x])
		{
			d.tex_x = d.frame_x * d.sprite_w + (x * d.sprite_w) / size;
			draw_sprite_column(&d);
		}
		x++;
	}
}
