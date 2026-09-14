/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_interact.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 16:45:41 by leggo             #+#    #+#             */
/*   Updated: 2026/05/27 12:00:00 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_door	*get_door_at(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->door_count)
	{
		if (game->doors[i].x == x && game->doors[i].y == y)
			return (&game->doors[i]);
		i++;
	}
	return (NULL);
}

int	is_door_blocking(t_game *game, double x, double y)
{
	int		i;
	int		tx;
	int		ty;
	t_door	*door;

	tx = (int)x;
	ty = (int)y;
	i = 0;
	while (i < game->door_count)
	{
		door = &game->doors[i];
		if (door->x == tx && door->y == ty && door->open_amount < 0.95)
			return (1);
		i++;
	}
	return (0);
}

static void	toggle_door_state(t_door *door)
{
	if (door->open_amount <= 0.0)
	{
		door->is_opening = 1;
		door->is_closing = 0;
	}
	else if (door->open_amount >= 1.0)
	{
		door->is_closing = 1;
		door->is_opening = 0;
	}
}

void	interact_with_doors(t_game *game)
{
	int		i;
	int		px;
	int		py;
	t_door	*door;

	px = (int)game->player->pos_x;
	py = (int)game->player->pos_y;
	i = 0;
	while (i < game->door_count)
	{
		door = &game->doors[i];
		if ((abs(door->x - px) <= 1 && door->y == py)
			|| (abs(door->y - py) <= 1 && door->x == px))
			toggle_door_state(door);
		i++;
	}
}

int	is_door_tile(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->door_count)
	{
		if (game->doors[i].x == x && game->doors[i].y == y)
			return (1);
		i++;
	}
	return (0);
}
