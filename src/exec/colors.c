/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:48:17 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/12 02:28:30 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	return ((r << 24) | (g << 16) | (b << 8) | 255);
}

uint32_t	get_texture_pixel(mlx_texture_t *texture, int tex_x, int tex_y)
{
	uint32_t	color;
	int			tex_offset;

	if (!texture)
		return (0xFFFFFFFF);
	if (tex_x < 0 || tex_x >= (int)texture->width || tex_y < 0 || tex_y >= (int)texture->height)
		return (0xFFFFFFFF);
	tex_offset = (tex_y * texture->width + tex_x) * 4;
	color = (texture->pixels[tex_offset] << 24)
		| (texture->pixels[tex_offset + 1] << 16)
		| (texture->pixels[tex_offset + 2] << 8)
		| (texture->pixels[tex_offset + 3]);
	return (color);
}

void	associate_color(t_game *game, char c, t_color rgb)
{
	if (c == 'F')
	{
		check_double(game, c);
		game->floor.r = rgb.r;
		game->floor.g = rgb.g;
		game->floor.b = rgb.b;
	}
	else if (c == 'C')
	{
		check_double(game, c);
		game->ceiling.r = rgb.r;
		game->ceiling.g = rgb.g;
		game->ceiling.b = rgb.b;
	}
}

