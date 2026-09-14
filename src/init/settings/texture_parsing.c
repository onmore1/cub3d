/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:38:39 by vananiev          #+#    #+#             */
/*   Updated: 2026/05/29 12:18:43 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_texture_file(char *path)
{
	int	fd;

	if (!path)
		return (printf("Error: invalid texture path\n"), 1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: %s: %s\n", path, strerror(errno));
		return (1);
	}
	close(fd);
	return (0);
}

int	extract_path(char *line, t_game *game, int direction)
{
	int		index;
	int		end;
	char	*path;

	if (game->walls[direction].path)
		return (printf("Error: duplicate texture\n"), 1);
	index = 2;
	while (line[index] == ' ')
		index++;
	end = index;
	while (line[end] && line[end] != '\n')
		end++;
	path = ft_substr(line, index, end - index);
	if (!path)
		return (1);
	if (check_texture_file(path))
		return (free(path), 1);
	game->walls[direction].path = path;
	return (0);
}
