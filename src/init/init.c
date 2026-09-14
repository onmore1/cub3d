/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 12:48:52 by vananiev          #+#    #+#             */
/*   Updated: 2026/06/12 11:48:03 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_game_nulls(t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	game->mouse_locked = 1;
	game->last_displayed_hp = -1;
	game->last_displayed_enemies = -1;
	game->last_displayed_ammo = -1;
}

static int	init_game_mlx(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	if (!game->mlx)
	{
		printf("Error: mlx_init failed\n");
		clean_up(game);
		exit(1);
	}
	return (0);
}

static int	find_spawn(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			if (check_player_spawn(game, x, y))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	init_player(t_game *game)
{
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		return (1);
	game->player->pitch = 0;
	game->player->health = 100;
	game->player->speed = 0;
	game->player->gun = NULL;
	game->player->legs = NULL;
	game->player->hands = NULL;
	if (find_spawn(game))
		return (0);
	free(game->player);
	game->player = NULL;
	return (printf("Error: no player spawn found\n"), 1);
}

t_game	*init_game(char *filename)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	init_game_nulls(game);
	game->map = init_map(filename);
	game->last_time = mlx_get_time();
	game->delta_time = 0.0;
	if (!game->map)
		return (printf("init map error\n"), clean_up(game), NULL);
	if (init_colors(game))
		return (printf("init colors error\n"), clean_up(game), NULL);
	if (init_textures(game))
		return (printf("init tex failed\n"), clean_up(game), NULL);
	if (init_sound(game))
		return (printf("init sound error\n"), clean_up(game), NULL);
	init_game_mlx(game);
	return (game);
}
