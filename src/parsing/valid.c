/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:33:17 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/13 14:59:39 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_player_pos(t_game *game)
{
	int			i;
	int			j;
	static int	k = 0;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
				|| game->map[i][j] == 'W' || game->map[i][j] == 'E')
			{
				if (k++ > 0)
				{
					printf("Error\nMultiple player\n");
					clean_game(game);
					exit(1);
				}
				game->player.x = j;
				game->player.y = i;
			}
			j++;
		}
		i++;
	}
}

void	validate_map_chars(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (!isvalidchar(game->map[i][j]) && game->map[i][j] != '\n')
			{
				printf("Error\nInvalid map\n");
				clean_game(game);
				exit(1);
			}
			j++;
		}
		i++;
	}
}

void	validate_flood_fill(char **map, int x, int y, t_game *game)
{
	if (x < 0 || y < 0 || y >= (int)ft_tablen(map)
		|| x >= (int)ft_strlen(map[y]))
	{
		printf("Error\nInvalid map 1\n");
		clean_game(game);
		exit(1);
	}
	if (map[y][x] == '1' || map[y][x] == 'x')
		return ;
	if (map[y][x] == ' ' || !isvalidchar(map[y][x]))
	{
		printf("Error\nInvalid map 2\n");
		clean_game(game);
		exit(1);
	}
	map[y][x] = 'x';
	validate_flood_fill(map, x - 1, y, game);
	validate_flood_fill(map, x + 1, y, game);
	validate_flood_fill(map, x, y - 1, game);
	validate_flood_fill(map, x, y + 1, game);
}
