/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 13:40:11 by vananiev          #+#    #+#             */
/*   Updated: 2026/05/26 11:55:41 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_wall_tex(t_ray *ray)
{
	if (ray->side == 0 && ray->step_x > 0)
		return (WEST);
	if (ray->side == 0 && ray->step_x < 0)
		return (EAST);
	if (ray->side == 1 && ray->step_y > 0)
		return (NORTH);
	return (SOUTH);
}

uint32_t	get_color(int r, int g, int b)
{
	return ((255 << 24) | (r << 16) | (g << 8) | b);
}

double	get_wall_x(t_game *game, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = game->player->pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = game->player->pos_x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	if (ray->hit_type == HIT_DOOR && ray->door)
	{
		wall_x += ray->door->open_amount;
		if (wall_x > 1.0)
			wall_x -= 1.0;
	}
	return (wall_x);
}

mlx_image_t	*get_tex(t_game *game, t_ray *ray)
{
	if (ray->hit_type == HIT_DOOR)
	{
		if (ray->door && ray->door->open_amount >= 1.0)
			return (NULL);
		return (game->door_tex);
	}
	return (game->walls[get_wall_tex(ray)].img);
}
