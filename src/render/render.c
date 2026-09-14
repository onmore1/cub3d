/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:45:35 by vananiev          #+#    #+#             */
/*   Updated: 2026/06/11 17:31:06 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray_steps_x(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player->pos_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player->pos_x)
			* ray->delta_dist_x;
	}
}

void	init_ray_steps_y(t_game *game, t_ray *ray)
{
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player->pos_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player->pos_y)
			* ray->delta_dist_y;
	}
}

static void	init_ray(t_game *game, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)WIDTH - 1.0;
	ray->dir_x = game->player->dir_x + game->player->plane_x * camera_x;
	ray->dir_y = game->player->dir_y + game->player->plane_y * camera_x;
	ray->map_x = (int)game->player->pos_x;
	ray->map_y = (int)game->player->pos_y;
	ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	ray->delta_dist_y = fabs(1.0 / ray->dir_y);
	init_ray_steps_x(game, ray);
	init_ray_steps_y(game, ray);
}

static void	cast_ray(t_game *game, int x)
{
	t_ray	ray;
	int		line_height;
	int		bounds[2];

	init_ray(game, &ray, x);
	dda(game, &ray);
	line_height = (int)(HEIGHT / ray.perp_wall_dist);
	bounds[0] = HEIGHT / 2 - line_height / 2 + game->player->pitch;
	bounds[1] = HEIGHT / 2 + line_height / 2 + game->player->pitch;
	if (bounds[0] < 0)
		bounds[0] = 0;
	if (bounds[1] >= HEIGHT)
		bounds[1] = HEIGHT - 1;
	draw_column(game, &ray, x, bounds);
	game->z_buffer[x] = ray.perp_wall_dist;
	if (x == WIDTH / 2)
		game->center_ray = ray;
}

void	render(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		cast_ray(game, x);
		x++;
	}
	render_enemies(game);
}
