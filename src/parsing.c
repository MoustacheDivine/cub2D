/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:48:53 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/10 00:44:30 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	parse_color(char *line, t_game *game, char c)
{
	char	**colors;
	long	r;
	long	g;
	long	b;

	colors = ft_split(clean_line(line), ',');
	r = ft_atoi_scam(colors[0]);
	g = ft_atoi_scam(colors[1]);
	b = ft_atoi_scam(colors[2]);
	if (r == ERROR_VALUE || g == ERROR_VALUE || b == ERROR_VALUE)
		(printf("Error\nInvalid color\n"), exit(1));
	if (c == 'F')
	{
		game->floor.r = r;
		game->floor.g = g;
		game->floor.b = b;
	}
	else if (c == 'C')
	{
		game->ceiling.r = r;
		game->ceiling.g = g;
		game->ceiling.b = b;
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

void	parse_texture(char *line, t_game *game, char c)
{
	char	*path;

	path = clean_line(line);
	load_texture(game, path, c);
	free(path);
}

void	parse_map_loop(int fd, t_game *game, char *line, char *file)
{
	char		**map;
	static int	i = 0;
	int			count;
	char		*tmp;

	count = get_map_len(line, fd, file);
	map = malloc(sizeof(char *) * (count + 1));
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_strtrim(line, " ");
		if (ft_strncmp(tmp, "1", 1) == 0 || ft_strncmp(tmp, "0", 1) == 0)
			break ;
		free(tmp);
		line = get_next_line(fd);
	}
	free(tmp);
	while (count > 0)
	{
		map[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
		count--;
	}
	map[i] = NULL;
	game->map = map;
	while (line)
	{
		if (line[0] != '1' && line[0] != ' '
			&& line[0] != '0' && line[0] != '\n')
		{
			printf("Error\nmap not at the end\n");
			free_map(game->map);
			exit(1);
		}
		free(line);
		line = get_next_line(fd);
	}
}

void check_all(t_game *game)
{
	char **cpy;

	check_end(game);
	check_all_data(game);
	get_player_pos(game);
	cpy = cpy_map(game);
	validate_map_chars(game);
	validate_flood_fill(cpy, game->player.x, game->player.y);
	free_map(cpy);
	get_player_dir(game);
}

int	parsing(char *map, t_game *game)
{
	char	*line;
	char	*tmp;
	int		fd;

	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_strtrim(line, " ");
		if (!cmp_line(tmp, game))
			;
		else if (ft_strncmp(tmp, "1", 1) == 0 || ft_strncmp(tmp, "0", 1) == 0)
		{
			parse_map_loop(fd, game, line, map);
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	check_all(game);
	return (0);
}
