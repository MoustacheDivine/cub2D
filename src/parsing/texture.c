/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:00:17 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/13 21:02:58 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_correct_texture(t_game *game, char c, char *line)
{
	if (c == 'N')
	{
		check_double(game, c, line);
		game->textures.n = game->texturetmp;
	}
	else if (c == 'S')
	{
		check_double(game, c, line);
		game->textures.s = game->texturetmp;
	}
	else if (c == 'W')
	{
		check_double(game, c, line);
		game->textures.w = game->texturetmp;
	}
	else if (c == 'E')
	{
		check_double(game, c, line);
		game->textures.e = game->texturetmp;
	}
}

void	load_texture(t_game *game, char *path, char c, char *line)
{
	game->texturetmp = mlx_load_png(path);
	game->path = path;
	if (!game->texturetmp)
	{
		printf("Error\nFailed to load texture\n");
		(free(path), free(game->line), free(game->tmp2), clean_game(game),
			exit(1));
	}
	load_correct_texture(game, c, line);
}
