/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_interact_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 12:00:00 by vananiev          #+#    #+#             */
/*   Updated: 2026/05/27 12:00:00 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_single_door(t_door *door, double delta_time)
{
	if (door->is_opening)
	{
		door->open_amount += door->speed * delta_time;
		if (door->open_amount >= 1.0)
		{
			door->open_amount = 1.0;
			door->is_opening = 0;
		}
	}
	if (door->is_closing)
	{
		door->open_amount -= door->speed * delta_time;
		if (door->open_amount <= 0.0)
		{
			door->open_amount = 0.0;
			door->is_closing = 0;
		}
	}
}

void	update_doors(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->door_count)
	{
		update_single_door(&game->doors[i], game->delta_time);
		i++;
	}
}

static int	check_horizontal_door(t_ray *ray, t_door *door, t_game *game)
{
	double	hit_y;
	double	opening;

	opening = door->open_amount;
	hit_y = game->player->pos_y + ray->perp_wall_dist * ray->dir_y;
	hit_y -= floor(hit_y);
	if (hit_y < 1.0 - opening)
		return (1);
	return (0);
}

static int	check_vertical_door(t_ray *ray, t_door *door, t_game *game)
{
	double	hit_x;
	double	opening;

	opening = door->open_amount;
	hit_x = game->player->pos_x + ray->perp_wall_dist * ray->dir_x;
	hit_x -= floor(hit_x);
	if (hit_x < 1.0 - opening)
		return (1);
	return (0);
}

int	hit_sliding_door(t_game *game, t_ray *ray, t_door *door)
{
	if (ray->side == 0)
		return (check_horizontal_door(ray, door, game));
	else
		return (check_vertical_door(ray, door, game));
}
