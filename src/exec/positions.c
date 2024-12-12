/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 07:14:57 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/12 10:03:42 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	**find_available_positions(t_game *game, int count, int map_y, int index)
{
	int	**positions;
	int	map_x;

	positions = malloc(count * sizeof(int *));
	if (!positions)
		return (NULL);
	while (game->map[map_y])
	{
		map_x = 0;
		while (game->map[map_y][map_x])
		{
			if (game->map[map_y][map_x] == '0')
			{
				positions[index] = malloc(2 * sizeof(int));
				positions[index][0] = map_x;
				positions[index][1] = map_y;
				index++;
			}
			map_x++;
		}
		map_y++;
	}
	return (positions);
}

int	count_available_positions(t_game *game)
{
	int	count;
	int	map_y;
	int	map_x;

	count = 0;
	map_y = 0;
	while (game->map[map_y])
	{
		map_x = 0;
		while (game->map[map_y][map_x])
		{
			if (game->map[map_y][map_x] == '0')
				count++;
			map_x++;
		}
		map_y++;
	}
	return (count);
}
