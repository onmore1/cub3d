/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory_stubs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 12:49:48 by vananiev          #+#    #+#             */
/*   Updated: 2026/06/11 15:00:00 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifndef BONUS

int	init_doors(t_game *game)
{
	(void)game;
	return (0);
}

int	init_enemies(t_game *game)
{
	(void)game;
	return (0);
}

void	render_enemies(t_game *game)
{
	(void)game;
}

int	init_sound(t_game *game)
{
	(void)game;
	return (0);
}

t_door	*get_door_at(t_game *game, int x, int y)
{
	(void)game;
	(void)x;
	(void)y;
	return (NULL);
}

#endif
