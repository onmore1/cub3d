/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 01:00:34 by cpinas            #+#    #+#             */
/*   Updated: 2026/06/17 16:46:21 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_if_map_start(char *line)
{
	int		index;
	int		len;

	len = 0;
	index = 0;
	while (line[index])
	{
		if (line[index] >= 0 && line[index] <= 32)
		{
			if (len < 3)
				len = 0;
			index++;
			continue ;
		}
		if (line[index] == '1')
		{
			index++;
			len++;
			continue ;
		}
		return (0);
	}
	return (len >= 3);
}

#ifdef BONUS

static int	check_valid_char(char c, int mode)
{
	if (!ft_strchr("013NSEWX \n", c) && mode == 1)
		return (printf("Error: Invalid char in map grid\n"), 0);
	else if (!ft_strchr("013NSEWX \n", c))
		return (0);
	return (1);
}
#else

static int	check_valid_char(char c, int mode)
{
	if (!ft_strchr("01NSEW \n", c) && mode == 1)
		return (printf("Error: Invalid char in map grid\n"), 0);
	else if (!ft_strchr("01NSEW \n", c))
		return (0);
	return (1);
}
#endif

int	is_map_line(char *line, int mode, t_map *map)
{
	int	i;

	i = 0;
	if (!line || !line[0])
		return (0);
	while (line[i] == ' ' || line[i] == '\n')
		i++;
	if (!line[i])
		return (0);
	while (line[i])
	{
		if (!check_valid_char(line[i], mode))
			return (0);
		if (line[i] == 'X')
			map->left++;
		i++;
	}
	return (1);
}

int	check_map(t_map *map)
{
	int	start;

	start = find_map_start(map);
	if (start == -1)
		return (1);
	if (build_grid(map, start))
		return (printf("Error: build_grid failed\n"), 1);
	if (normalize_grid(map))
		return (printf("Error: normalize failed\n"), 1);
	if (find_player_start(map))
		return (1);
	if (validate_map_enclosed(map))
		return (1);
	return (0);
}
