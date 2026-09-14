/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 12:49:48 by vananiev          #+#    #+#             */
/*   Updated: 2026/06/11 15:00:00 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_input(t_game *game)
{
	if (check_settings(game))
		return (1);
	if (check_map(game->map))
		return (1);
	if (init_doors(game))
		return (printf("Error: failed to init doors\n"), 1);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
		return (printf("Error: invalid argument count\n"), 1);
	game = init_game(av[1]);
	if (!game)
		return (1);
	if (check_input(game))
		return (clean_up(game), 1);
	if (init_player(game))
		return (clean_up(game), 1);
	if (init_enemies(game))
		return (clean_up(game), 1);
	if (malloc_field_dist(game))
		return (clean_up(game), 1);
	if (load_assets(game))
		return (clean_up(game), 1);
	start(game);
	return (clean_up(game), 0);
}
