/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:31:25 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/10 13:41:14 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static long	loop_scam(int *i, const char *str)
{
	long	result;

	result = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		result *= 10;
		result += str[(*i)++] - '0';
	}
	return (result);
}

long	ft_atoi_scam(const char *str)
{
	int		i;
	long	result;
	int		sign;

	sign = 1;
	i = 0;
	result = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] != '+' && str[i] != '-' && !ft_isdigit(str[i]))
		return (ERROR_VALUE);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	result = loop_scam(&i, str);
	result *= sign;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '\0' && result >= -2147483648 && result <= 2147483647)
		return (result);
	return (ERROR_VALUE);
}

int	cmp_line(char *tmp, t_game *game)
{
	if (!ft_strncmp(tmp, "NO ", 3))
		parse_texture(tmp + 2, game, 'N');
	else if (!ft_strncmp(tmp, "SO ", 3))
		parse_texture(tmp + 2, game, 'S');
	else if (!ft_strncmp(tmp, "WE ", 3))
		parse_texture(tmp + 2, game, 'W');
	else if (!ft_strncmp(tmp, "EA ", 3))
		parse_texture(tmp + 2, game, 'E');
	else if (!ft_strncmp(tmp, "F ", 2))
		parse_color(tmp + 1, game, 'F');
	else if (!ft_strncmp(tmp, "C ", 2))
		parse_color(tmp + 1, game, 'C');
	else
		return (1);
	return (0);
}

char	*clean_line(char *line)
{
	char *trimmed;
	char *cleaned;

	trimmed = ft_strtrim(line, " ");
	cleaned = ft_strtrim(trimmed, "\n");
	free(trimmed);
	return (cleaned);
}

void	check_double(t_game *game, char c)
{
	if (c == 'N' && game->textures.n)
	{
		printf("Error\ndouble textures\n");
		exit(1);
	}
	else if (c == 'S' && game->textures.s)
	{
		printf("Error\ndouble textures\n");
		exit(1);
	}
	else if (c == 'W' && game->textures.w)
	{
		printf("Error\ndouble textures\n");
		exit(1);
	}
	else if (c == 'E' && game->textures.e)
	{
		printf("Error\ndouble textures\n");
		exit(1);
	}
}
