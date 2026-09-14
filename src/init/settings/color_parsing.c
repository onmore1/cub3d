/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:37:01 by vananiev          #+#    #+#             */
/*   Updated: 2026/06/12 14:59:28 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_color_helper(int *rgb)
{
	int	index;

	index = 0;
	while (index < 3)
	{
		if (rgb[index] < 0)
			return (printf("Error: color value cannot be negative\n"), 1);
		if (rgb[index] > 255)
			return (printf("Error: color value cannot exceed 255\n"), 1);
		index++;
	}
	return (0);
}

static int	check_color(char **values, char *trimmed)
{
	int	index;

	index = 0;
	if (!values)
		return (printf("Error: invalid color format\n"), free(trimmed), 1);
	while (index < 3)
	{
		if (!values[index])
		{
			printf("Error: missing color value\n");
			return (free_double_pointer(values), free(trimmed), 1);
		}
		if (!is_digits_only(values[index]))
		{
			printf("Error: color values must be digits only\n");
			return (free_double_pointer(values), free(trimmed), 1);
		}
		index++;
	}
	if (values[3] != NULL)
	{
		printf("Error: too many color values\n");
		return (free_double_pointer(values), free(trimmed), 1);
	}
	return (0);
}

int	extract_color(char *line, int *rgb)
{
	char	*trimmed;
	char	**values;
	int		index;
	int		end;

	index = 1;
	while (line[index] == ' ')
		index++;
	end = index;
	while (line[end] && line[end] != '\n')
		end++;
	trimmed = ft_substr(line, index, end - index);
	if (!trimmed)
		return (1);
	values = ft_split(trimmed, ',');
	if (check_color(values, trimmed))
		return (1);
	rgb[RED] = ft_atoi(values[0]);
	rgb[GREEN] = ft_atoi(values[1]);
	rgb[BLUE] = ft_atoi(values[2]);
	free_double_pointer(values);
	free(trimmed);
	if (check_color_helper(rgb))
		return (1);
	return (0);
}
