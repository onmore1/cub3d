/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 12:00:00 by vananiev          #+#    #+#             */
/*   Updated: 2026/05/27 12:00:00 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	*init_bfs_queue(t_game *game, int player[2])
{
	int	*queue;

	player[POS_X] = (int)game->player->pos_x;
	player[POS_Y] = (int)game->player->pos_y;
	if (!is_walkable_tile(game, player[POS_X], player[POS_Y]))
		return (NULL);
	reset_dist_field(game);
	queue = malloc(sizeof(int) * game->map->width * game->map->height);
	if (!queue)
		return (NULL);
	game->dist_field[player[POS_Y]][player[POS_X]] = 0;
	queue[0] = player[POS_Y] * game->map->width + player[POS_X];
	return (queue);
}

void	compute_dist_field(t_game *game)
{
	int	*queue;
	int	head;
	int	tail;
	int	player[2];
	int	curr[2];

	queue = init_bfs_queue(game, player);
	if (!queue)
		return ;
	head = 0;
	tail = 1;
	while (head < tail)
	{
		curr[POS_X] = queue[head] % game->map->width;
		curr[POS_Y] = queue[head] / game->map->width;
		push_neighbors(game, curr, queue, &tail);
		head++;
	}
	free(queue);
}

static int	check_neighbor(t_game *game, int coords[4], int *best,
		int next[2])
{
	int	nx;
	int	ny;
	int	dist;

	nx = coords[NEIGHBOR_X];
	ny = coords[NEIGHBOR_Y];
	if (!is_walkable_tile(game, nx, ny))
		return (0);
	dist = game->dist_field[ny][nx];
	if (dist == -1 || dist >= *best)
		return (0);
	*best = dist;
	next[POS_X] = nx;
	next[POS_Y] = ny;
	return (1);
}

int	enemy_next_step(t_game *game, int enemy_i, int next[2])
{
	static const int	dx[4] = {1, -1, 0, 0};
	static const int	dy[4] = {0, 0, 1, -1};
	int					coords[4];
	int					best;
	int					i;

	coords[CURRENT_X] = (int)game->enemies[enemy_i].x;
	coords[CURRENT_Y] = (int)game->enemies[enemy_i].y;
	if (!is_walkable_tile(game, coords[CURRENT_X], coords[CURRENT_Y]))
		return (0);
	if (game->dist_field[coords[CURRENT_Y]][coords[CURRENT_X]] <= 0)
		return (0);
	best = game->dist_field[coords[CURRENT_Y]][coords[CURRENT_X]];
	next[POS_X] = -1;
	i = 0;
	while (i < 4)
	{
		coords[NEIGHBOR_X] = coords[CURRENT_X] + dx[i];
		coords[NEIGHBOR_Y] = coords[CURRENT_Y] + dy[i];
		if (!already_occupied(game, enemy_i, coords[NEIGHBOR_X],
				coords[NEIGHBOR_Y]))
			check_neighbor(game, coords, &best, next);
		i++;
	}
	return (next[POS_X] != -1);
}
