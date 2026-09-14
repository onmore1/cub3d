/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 12:46:45 by cpinas            #+#    #+#             */
/*   Updated: 2026/05/27 12:00:00 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_enemies(t_map *map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] == 'X')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

static void	init_single_enemy(t_enemy *e, int x, int y)
{
	e->x = x + 0.5;
	e->y = y + 0.5;
	e->hp = 100;
	e->alive = 1;
	e->anim_frame = 0;
	e->anim_timer = 0;
	e->hurt = 0;
	e->hurt_timer = 0;
	e->moving = 0;
	e->close = 0;
	e->attacking = 0;
	e->tried_to_attack = 0;
	e->knockback = 0;
	e->turn_timer = 2;
	e->spotted = 0;
	e->marked = 0;
	e->last_time = mlx_get_time();
}

static void	fill_enemy_grid(t_game *game, int *index)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map->height)
	{
		j = 0;
		while (j < game->map->width)
		{
			if (game->map->grid[i][j] == 'X')
			{
				init_single_enemy(&game->enemies[*index], j, i);
				(*index)++;
			}
			j++;
		}
		i++;
	}
}

int	init_enemies(t_game *game)
{
	int	index;

	game->enemy_count = count_enemies(game->map);
	if (game->enemy_count == 0)
		return (0);
	game->enemies = malloc(sizeof(t_enemy) * game->enemy_count);
	if (!game->enemies)
		return (1);
	index = 0;
	fill_enemy_grid(game, &index);
	game->map->left = game->enemy_count;
	return (0);
}
