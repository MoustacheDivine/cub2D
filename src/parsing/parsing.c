/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:48:53 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/14 01:56:37 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_color(char *line, t_game *game, char c, char *tofree)
{
	char	**colors;
	t_color	rgb;
	char	*tmp;
	int		i;

	i = -1;
	tmp = clean_line(line, game);
	colors = ft_split(tmp, ',');
	check_colors(colors, tofree, tmp, game);
	rgb.r = ft_atoi_scam(colors[0]);
	rgb.g = ft_atoi_scam(colors[1]);
	rgb.b = ft_atoi_scam(colors[2]);
	if (rgb.r == ERROR_VALUE || rgb.g == ERROR_VALUE || rgb.b == ERROR_VALUE)
	{
		printf("Error\nInvalid color\n");
		while (colors[++i])
			free(colors[i]);
		(free(colors), free(tofree), free(tmp), free(game->line));
		clean_game(game);
	}
	while (colors[++i])
		free(colors[i]);
	free(colors);
	free(tmp);
	associate_color(game, c, rgb);
}

void	parse_texture(char *line, t_game *game, char c)
{
	char	*path;

	path = clean_line(line, game);
	load_texture(game, path, c, line);
	free(path);
}

void	parse_map_loop(t_game *game, char *line, char *file)
{
	char	**map;
	int		count;

	count = get_map_len(line, game, file);
	line = get_next_line(game->fd);
	map = get_back_to_map(line, game, count);
	line = get_next_line(game->fd);
	game->map = map;
	check_end(game, line, game->fd);
}

void	parse_file(t_game *game, char *map)
{
	char	*tmp;

	while (game->line)
	{
		tmp = ft_strdup(game->line);
		game->tmp2 = tmp;
		while (*tmp == ' ')
			tmp++;
		if (ft_strncmp(tmp, "1", 1) != 0 && ft_strncmp(tmp, "0", 1) != 0)
			cmp_line(tmp, game);
		else if (ft_strncmp(tmp, "1", 1) == 0 || ft_strncmp(tmp, "0", 1) == 0)
		{
			free(game->tmp2);
			game->tmp2 = NULL;
			parse_map_loop(game, game->line, map);
			break ;
		}
		free(game->line);
		if (game->tmp2)
			free(game->tmp2);
		game->tmp2 = NULL;
		game->line = get_next_line(game->fd);
	}
}

int	parsing(char *map, t_game *game)
{
	game->fd = open(map, O_RDONLY);
	if (game->fd < 0)
	{
		printf("Error\nInvalid file\n");
		clean_game(game);
	}
	game->line = get_next_line(game->fd);
	parse_file(game, map);
	if (game->tmp2)
		free(game->tmp2);
	close(game->fd);
	game->fd = -1;
	check_all(game);
	return (0);
}
