/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_guy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 14:00:00 by vananiev          #+#    #+#             */
/*   Updated: 2026/05/28 14:54:30 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_if_end(t_game *game)
{
	int	hp;

	hp = game->player->health;
	if (!game->map->left || game->player->health <= 0)
	{
		mlx_close_window(game->mlx);
		if (game->player->health <= 0)
			write(1, "You died :(\n", 12);
		else
			write(1, "You won!\n", 9);
		return ;
	}
	else if (hp > 75)
		game->doom_guy->current_path = 0;
	else if (hp > 50)
		game->doom_guy->current_path = 1;
	else if (hp > 25)
		game->doom_guy->current_path = 2;
	else
		game->doom_guy->current_path = 3;
}

void	got_hurt(double now, t_doom_guy *doom_guy)
{
	mlx_image_t	**set;

	set = doom_guy->imgs[doom_guy->current_path];
	set[doom_guy->current]->instances[0].enabled = false;
	set[4]->instances[0].enabled = false;
	set[3]->instances[0].enabled = true;
	if ((now - doom_guy->last_time) * 1000 >= doom_guy->delay[1])
	{
		set[3]->instances[0].enabled = false;
		set[doom_guy->current]->instances[0].enabled = true;
		doom_guy->last_time = now;
		doom_guy->face = DEFAULT;
	}
}

void	got_happy(double now, t_doom_guy *doom_guy)
{
	mlx_image_t	**set;

	set = doom_guy->imgs[doom_guy->current_path];
	set[doom_guy->current]->instances[0].enabled = false;
	set[3]->instances[0].enabled = false;
	set[4]->instances[0].enabled = true;
	if ((now - doom_guy->last_time) * 1000 >= doom_guy->delay[2])
	{
		set[4]->instances[0].enabled = false;
		set[doom_guy->current]->instances[0].enabled = true;
		doom_guy->last_time = now;
		doom_guy->face = DEFAULT;
	}
}
