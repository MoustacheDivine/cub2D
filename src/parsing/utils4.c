/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:51:07 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/11 19:49:28 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void display_map(t_game *game)
{
	int i = 0;
	while (game->map[i])
	{
		printf("%s\n", game->map[i]);
		i++;
	}
}

void	load_texture(t_game *game, char *path, char c)
{
	void	*texture;

	texture = mlx_load_png(path);
	if (!texture)
		(printf("Error\nFailed to load texture\n"), free(path), exit(1));
	if (c == 'N')
	{
		check_double(game, c);
		game->textures.n = texture;
	}
	else if (c == 'S')
	{
		check_double(game, c);
		game->textures.s = texture;
	}
	else if (c == 'W')
	{
		check_double(game, c);
		game->textures.w = texture;
	}
	else if (c == 'E')
	{
		check_double(game, c);
		game->textures.e = texture;
	}
}

char	**cpy_map(t_game *game)
{
	int		i;
	char	**map;

	i = 0;
	map = malloc(sizeof(char *) * (ft_tablen(game->map) + 1));
	while (game->map[i])
	{
		map[i] = ft_strdup(game->map[i]);
		i++;
	}
	map[i] = NULL;
	return (map);
}

char	**get_back_to_map(char *line, int fd, int count)
{
	char	*tmp;
	char **map;
	int i;

	i = 0;
	map = malloc(sizeof(char *) * (count + 1));
	while (line)
	{
		tmp = ft_strtrim(ft_strdup(line), " ");
		if (ft_strncmp(tmp, "1", 1) == 0 || ft_strncmp(tmp, "0", 1) == 0)
			break ;
		free(tmp);
		free(line);
		line = get_next_line(fd);
	}
	while (count > 0 && line)
	{
		map[i] = ft_strdup(line);
		i++;
		free(line);
		line = get_next_line(fd);
		count--;
	}
	map[i] = NULL;
	free(tmp);
	return (map);
}

void	parse_map_loop(int fd, t_game *game, char *line, char *file)
{
	char		**map;
	//static int	i = 0;
	int			count;

	count = get_map_len(line, fd, file);
	//map = malloc(sizeof(char *) * (count + 1));
	line = get_next_line(fd);
	map = get_back_to_map(line, fd, count);
	line = get_next_line(fd);
	// while (count > 0 && line)
	// {
	// 	map[i] = ft_strdup(line);
	// 	i++;
	// 	free(line);
	// 	line = get_next_line(fd);
	// 	count--;
	// }
	//map[i] = NULL;
	game->map = map;
	display_map(game);
	check_end(game, line, fd);
}

