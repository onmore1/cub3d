/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 12:00:00 by vananiev          #+#    #+#             */
/*   Updated: 2026/05/28 10:47:30 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pixel(uint32_t *frame, mlx_image_t *tex,
	int coords[2], int tex_data[2])
{
	int			tex_y;
	int			pixel_index;
	int			screen_index;
	uint32_t	texture_color;

	tex_y = tex_data[TEX_Y] % tex->height;
	pixel_index = tex_y * tex->width * 4 + tex_data[TEX_X] * 4;
	texture_color = *(uint32_t *)&tex->pixels[pixel_index];
	screen_index = coords[TEX_Y] * WIDTH + coords[TEX_X];
	frame[screen_index] = texture_color;
}

int	get_tex_x(mlx_image_t *tex, double wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * tex->width);
	if (tex_x >= (int)tex->width)
		tex_x = tex->width - 1;
	return (tex_x);
}
