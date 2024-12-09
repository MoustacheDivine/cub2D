/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:09:50 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/09 22:20:01 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_game game;
	int ret;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <map.cub>\n", argv[0]);
		return (1);
	}


	// Initialize game structure to safe defaults before parsing
	// Assuming t_game has textures and colors properly defined
	// For example:
	game.textures.n = NULL;
	game.textures.s = NULL;
	game.textures.w = NULL;
	game.textures.e = NULL;
	game.floor = (t_color){-1,-1,-1};
	game.ceiling = (t_color){-1,-1,-1};
	// You might do something like:
	// ft_bzero(&game, sizeof(t_game));

	ret = parsing(argv[1], &game);

	if (ret != 0)
	{
		fprintf(stderr, "Error: Parsing failed\n");
		return (1);
	}

	// If parsing succeeds, print out the results to verify
	// For instance:
	printf("North texture: %p\n", (void *)game.textures.n);
	printf("South texture: %p\n", (void *)game.textures.s);
	printf("West  texture: %p\n", (void *)game.textures.w);
	printf("East  texture: %p\n", (void *)game.textures.e);

	printf("Floor color: R=%d G=%d B=%d\n", game.floor.r, game.floor.g,
		game.floor.b);
	printf("Ceiling color: R=%d G=%d B=%d\n", game.ceiling.r, game.ceiling.g,
		game.ceiling.b);

	// If you have a map loaded, print it
	if (game.map)
	{
		int i = 0;
		printf("Map:\n");
		while (game.map[i])
		{
			printf("%s", game.map[i]);
			i++;
		}
	}

	return (0);
}