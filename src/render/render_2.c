/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:16:00 by vananiev          #+#    #+#             */
/*   Updated: 2026/05/28 10:42:32 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_ceiling(uint32_t *frame, t_game *game, int x, int end)
{
	uint32_t	color;
	int			y;

	color = get_color(game->colors[CEILING][RED],
			game->colors[CEILING][GREEN], game->colors[CEILING][BLUE]);
	y = 0;
	while (y < end)
	{
		frame[y * WIDTH + x] = color;
		y++;
	}
}

static void	draw_wall_loop(uint32_t *frame, mlx_image_t *tex,
		int x, double params[4])
{
	int		coords[2];
	int		tex_data[2];
	double	tex_pos;
	double	tex_step;
	int		line_height;

	line_height = (int)(HEIGHT / params[PERP_DIST]);
	tex_step = (double)tex->height / line_height;
	tex_pos = ((int)params[DRAW_START]
			- (HEIGHT / 2 - line_height / 2 + (int)params[4]))
		* tex_step;
	coords[X] = x;
	coords[Y] = (int)params[DRAW_START];
	tex_data[TEX_X] = (int)params[TEX_X_PARAM];
	while (coords[Y] < (int)params[DRAW_END])
	{
		tex_data[TEX_Y] = (int)tex_pos;
		draw_pixel(frame, tex, coords, tex_data);
		tex_pos += tex_step;
		coords[Y]++;
	}
}

static void	draw_wall_slice(t_game *game, t_ray *ray, int x, int bounds[2])
{
	uint32_t	*frame;
	mlx_image_t	*tex;
	double		params[5];

	frame = (uint32_t *)game->frame->pixels;
	tex = get_tex(game, ray);
	if (!tex)
		return ;
	params[DRAW_START] = bounds[0];
	params[TEX_X_PARAM] = get_tex_x(tex, get_wall_x(game, ray));
	params[PERP_DIST] = ray->perp_wall_dist;
	params[DRAW_END] = bounds[1];
	params[4] = game->player->pitch;
	draw_wall_loop(frame, tex, x, params);
}

static void	draw_floor(uint32_t *frame, t_game *game, int x, int start)
{
	uint32_t	color;
	int			y;

	color = get_color(game->colors[FLOOR][RED],
			game->colors[FLOOR][GREEN], game->colors[FLOOR][BLUE]);
	y = start;
	while (y < HEIGHT)
	{
		frame[y * WIDTH + x] = color;
		y++;
	}
}

void	draw_column(t_game *game, t_ray *ray, int x, int bounds[2])
{
	uint32_t	*frame;

	frame = (uint32_t *)game->frame->pixels;
	draw_ceiling(frame, game, x, bounds[0]);
	draw_wall_slice(game, ray, x, bounds);
	draw_floor(frame, game, x, bounds[1]);
}
