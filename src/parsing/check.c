/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 02:27:50 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/12 02:29:37 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_all(t_game *game)
{
	char	**cpy;

	check_all_data(game);
	get_player_pos(game);
	cpy = cpy_map(game);
	validate_map_chars(game);
	validate_flood_fill(cpy, game->player.x, game->player.y);
	get_map_dimension(game);
	free_map(cpy);
}

void	check_double(t_game *game, char c)
{
	if (c == 'N' && game->textures.n)
		error_double(1);
	else if (c == 'S' && game->textures.s)
		error_double(1);
	else if (c == 'W' && game->textures.w)
		error_double(1);
	else if (c == 'E' && game->textures.e)
		error_double(1);
	else if (c == 'F' && game->floor.r >= 0)
		error_double(2);
	else if (c == 'C' && game->ceiling.r >= 0)
		error_double(2);
}

int	isvalidchar(char c)
{
	return (c == ' ' || c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'W'
		|| c == 'E' || c == 'D');
}

void	check_end(t_game *game, char *line, int fd)
{
	while (line)
	{
		if (line[0] != '1' && line[0] != ' ' && line[0] != '0'
			&& line[0] != '\n')
		{
			printf("Error\nmap not at the end\n");
			free_map(game->map);
			exit(1);
		}
		free(line);
		line = get_next_line(fd);
	}
}

void	check_all_data(t_game *game)
{
	if (!game->textures.n || !game->textures.s || !game->textures.w
		|| !game->textures.e)
	{
		printf("Error\nMissing texture\n");
		exit(1);
	}
	if (game->floor.r < 0 || game->floor.g < 0 || game->floor.b < 0)
	{
		printf("Error\nMissing floor color\n");
		exit(1);
	}
	if (game->ceiling.r < 0 || game->ceiling.g < 0 || game->ceiling.b < 0)
	{
		printf("Error\nMissing ceiling color\n");
		exit(1);
	}
}