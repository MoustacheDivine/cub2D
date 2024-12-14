/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:31:25 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/14 01:43:03 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_cub(char *fichier)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(fichier);
	if (len < 4)
	{
		printf("Error\nInvalid file\n");
		exit(0);
	}
	while (fichier[i])
		i++;
	if (fichier[i - 1] != 'b' || fichier[i - 2] != 'u' || fichier[i - 3] != 'c'
		|| fichier[i - 4] != '.')
	{
		printf("Error\nInvalid file\n");
		exit(0);
	}
}

int	cmp_line(char *tmp, t_game *game)
{
	char	*tmp2;

	tmp2 = tmp;
	if (ft_strncmp(tmp, "NO ", 3) == 0)
		parse_texture(tmp + 3, game, 'N');
	else if (ft_strncmp(tmp, "SO ", 3) == 0)
		parse_texture(tmp + 3, game, 'S');
	else if (ft_strncmp(tmp, "WE ", 3) == 0)
		parse_texture(tmp + 3, game, 'W');
	else if (ft_strncmp(tmp, "EA ", 3) == 0)
		parse_texture(tmp + 3, game, 'E');
	else if (ft_strncmp(tmp, "F ", 2) == 0)
		parse_color(tmp + 2, game, 'F', tmp2);
	else if (ft_strncmp(tmp, "C ", 2) == 0)
		parse_color(tmp + 2, game, 'C', tmp2);
	else if (tmp[0] == '\n' || tmp[0] == '\0')
		;
	else
	{
		printf("Error\nInvalid line\n");
		free(game->line);
		free(game->tmp2);
		clean_game(game);
	}
	return (0);
}

char	*clean_line(char *line, t_game *game)
{
	char	*cleaned;

	if (line[0] == '\n')
	{
		printf("Error\nInvalid line\n");
		clean_game(game);
	}
	cleaned = ft_strtrim(line, " \n");
	return (cleaned);
}

void	error_double(int i, t_game *game, char *line)
{
	if (i == 1)
	{
		printf("Error\nDouble textures\n");
		if (game->texturetmp)
			mlx_delete_texture(game->texturetmp);
		if (game->path)
			free(game->path);
		free(game->line);
		free(game->tmp2);
		clean_game(game);
	}
	else if (i == 2)
	{
		printf("Error\nDouble colors\n");
		free(line);
		free(game->line);
		free(game->tmp2);
		clean_game(game);
	}
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
