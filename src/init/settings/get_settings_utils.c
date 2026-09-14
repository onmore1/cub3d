/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_settings_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:43:11 by vananiev          #+#    #+#             */
/*   Updated: 2026/04/30 14:14:52 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	check_if_cardinal_direction(char *line)
{
	if (!line || !line[0] || !line[1] || !line[2])
		return (-1);
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		return (NORTH);
	if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		return (SOUTH);
	if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		return (WEST);
	if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		return (EAST);
	return (-1);
}

int	check_if_surface(char *line)
{
	if (!line || !line[0] || !line[1])
		return (-1);
	if (line[0] == 'F' && line[1] == ' ')
		return (FLOOR);
	if (line[0] == 'C' && line[1] == ' ')
		return (CEILING);
	return (-1);
}

void	set_direction_helper(t_player *player, char spawn)
{
	if (spawn == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 1;
	}
	else if (spawn == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -1;
	}
}

void	set_direction(t_player *player, char spawn)
{
	if (spawn == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = 1;
		player->plane_y = 0;
	}
	else if (spawn == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = -1;
		player->plane_y = 0;
	}
	else
		set_direction_helper(player, spawn);
}
