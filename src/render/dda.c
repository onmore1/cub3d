/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:05:40 by vananiev          #+#    #+#             */
/*   Updated: 2026/06/11 17:31:22 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_single_enemy(t_enemy *enemy,
	double rx, double ry)
{
	double	dx;
	double	dy;
	double	dist_sq;

	dx = enemy->x - rx;
	dy = enemy->y - ry;
	dist_sq = dx * dx + dy * dy;
	if (dist_sq < 0.5)
	{
		enemy->marked = 1;
		enemy->spotted = 1;
		enemy->spot_time = mlx_get_time();
	}
}

void	check_if_enemy_spotted(t_game *game, t_ray *ray)
{
	int		i;
	double	ray_x;
	double	ray_y;

	ray_x = ray->map_x + 0.5;
	ray_y = ray->map_y + 0.5;
	i = 0;
	while (i < game->enemy_count)
	{
		if (game->enemies[i].alive)
			check_single_enemy(&game->enemies[i], ray_x, ray_y);
		i++;
	}
}

void	dda_step(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

static int	process_dda_cell(t_game *game, t_ray *ray, t_door *door)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player->pos_x
				+ (1 - ray->step_x) / 2.0) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player->pos_y
				+ (1 - ray->step_y) / 2.0) / ray->dir_y;
	if (game->map->grid[ray->map_y][ray->map_x] == '1')
	{
		ray->hit_type = HIT_WALL;
		return (1);
	}
	if (door && hit_sliding_door(game, ray, door))
	{
		ray->hit_type = HIT_DOOR;
		ray->door = door;
		return (1);
	}
	return (0);
}

void	dda(t_game *game, t_ray *ray)
{
	t_door	*door;

	ray->hit_type = HIT_NONE;
	ray->door = NULL;
	ray->perp_wall_dist = 0.0;
	while (1)
	{
		dda_step(ray);
		if (ray->map_x < 0 || ray->map_x >= game->map->width
			|| ray->map_y < 0 || ray->map_y >= game->map->height)
			break ;
		door = get_door_at(game, ray->map_x, ray->map_y);
		if (process_dda_cell(game, ray, door))
			break ;
		check_if_enemy_spotted(game, ray);
	}
	if (ray->perp_wall_dist < 0.05)
		ray->perp_wall_dist = 0.05;
}
