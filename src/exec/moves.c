/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 04:47:38 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/10 14:47:00 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.dir_x * MOVE_SPEED;
	new_y = game->player.y + game->player.dir_y * MOVE_SPEED;
	if (game->map[(int)new_y][(int)game->player.x] != '1')
		game->player.y = new_y;
	if (game->map[(int)game->player.y][(int)new_x] != '1')
		game->player.x = new_x;
	render(game);
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.dir_x * MOVE_SPEED;
	new_y = game->player.y - game->player.dir_y * MOVE_SPEED;
	if (game->map[(int)new_y][(int)game->player.x] != '1')
		game->player.y = new_y;
	if (game->map[(int)game->player.y][(int)new_x] != '1')
		game->player.x = new_x;
	render(game);
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.plane_x * MOVE_SPEED;
	new_y = game->player.y - game->player.plane_y * MOVE_SPEED;
	if (game->map[(int)new_y][(int)game->player.x] != '1')
		game->player.y = new_y;
	if (game->map[(int)game->player.y][(int)new_x] != '1')
		game->player.x = new_x;
	render(game);
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.plane_x * MOVE_SPEED;
	new_y = game->player.y + game->player.plane_y * MOVE_SPEED;
	if (game->map[(int)new_y][(int)game->player.x] != '1')
		game->player.y = new_y;
	if (game->map[(int)game->player.y][(int)new_x] != '1')
		game->player.x = new_x;
	render(game);
}

void	rotate_player(t_game *game, double rotation_speed)
{
	double old_dir_x = game->player.dir_x;
	double old_plane_x = game->player.plane_x;
	game->player.dir_x = game->player.dir_x * cos(rotation_speed)
		- game->player.dir_y * sin(rotation_speed);
	game->player.dir_y = old_dir_x * sin(rotation_speed) + game->player.dir_y
		* cos(rotation_speed);
	game->player.plane_x = game->player.plane_x * cos(rotation_speed)
		- game->player.plane_y * sin(rotation_speed);
	game->player.plane_y = old_plane_x * sin(rotation_speed)
		+ game->player.plane_y * cos(rotation_speed);
	render(game);
}
