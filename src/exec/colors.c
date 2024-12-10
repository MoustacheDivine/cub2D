/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:48:17 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/10 10:49:04 by gbruscan         ###   ########.fr       */
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
		return (0xFFFFFFFF); // Blanc par défaut
	tex_offset = (tex_y * texture->width + tex_x) * 4;
	color = (texture->pixels[tex_offset] << 24)
		| (texture->pixels[tex_offset + 1] << 16)
		| (texture->pixels[tex_offset + 2] << 8)
		| (texture->pixels[tex_offset + 3]);
	return (color);
}
