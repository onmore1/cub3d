/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 12:49:17 by vananiev          #+#    #+#             */
/*   Updated: 2026/06/17 16:45:23 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_double_pointer(char **arr)
{
	int	index;

	if (!arr)
		return ;
	index = 0;
	while (arr[index])
	{
		if (arr[index])
			free(arr[index++]);
	}
	free(arr);
}

void	free_double_pointer_int(int **arr)
{
	int	index;

	index = 0;
	while (arr[index])
		free(arr[index++]);
	free(arr);
}

int	malloc_field_dist(t_game *game)
{
	int	y;

	y = 0;
	game->dist_field = malloc(sizeof(int *) * (game->map->height + 1));
	if (!game->dist_field)
		return (clean_up(game), 1);
	while (y < game->map->height)
	{
		game->dist_field[y] = malloc(sizeof(int) * game->map->width);
		if (!game->dist_field[y])
			return (game->dist_field[y] = NULL, clean_up(game), 1);
		y++;
	}
	game->dist_field[y] = NULL;
	return (0);
}

int	is_digits_only(char *str)
{
	int	index;

	index = 0;
	if (!str || !str[0])
		return (0);
	while (str[index])
	{
		if (str[index] < '0' || str[index] > '9')
			return (0);
		index++;
	}
	return (1);
}

int	check_if_empty_line(char *line)
{
	int	index;

	index = 0;
	while (line[index])
	{
		if (line[index] < 0 || line[index] > 32)
			return (0);
		index++;
	}
	return (1);
}
